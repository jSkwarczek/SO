package main

import (
	"bufio"
	"fmt"
	"net"
	"os"

	rl "github.com/gen2brain/raylib-go/raylib"
)

const Size = 13

var messages [Size]string
var last_msg int

func isKeyPressed() bool {
	keyPressed := false
	key := rl.GetKeyPressed()

	if (key >= 32) && (key <= 126) {
		keyPressed = true
	}

	return keyPressed
}

func setupConn(ip string, port string) net.Conn {
	addr, err := net.ResolveTCPAddr("tcp", ip+":"+port)
	if err != nil {
		fmt.Println("Błąd przy rozwiązywaniu adresu:", err)
		os.Exit(3)
	}

	conn, err := net.DialTCP("tcp", nil, addr)
	if err != nil {
		fmt.Println("Błąd przy nawiązywaniu połączenia:", err)
		os.Exit(3)
	}

	return conn
}

func receiveMsg(conn net.Conn) {
	reader := bufio.NewReader(conn)
	for {
		message, err := reader.ReadString('\n')
		if err != nil {
			conn.Close()
			os.Exit(3)
		}
		fmt.Printf("Message incoming: %s", string(message))
		messages[last_msg] = message
		last_msg = (last_msg + 1) % Size
	}
}

func msgInit() {
	for k := 0; k < 13; k++ {
		messages[k] = ""
	}
}

func main() {
	rl.InitWindow(800, 450, "SysOpy - chat")
	defer rl.CloseWindow()

	conn := setupConn("192.168.179.129", "8080")
	defer conn.Close()

	msgInit()
	last_msg = 0
	go receiveMsg(conn)

	toPrint := [Size]string{"", "", "", "", "", "", "", "", "", "", "", "", ""}

	name := ""

	textBox := rl.Rectangle{X: 25.0, Y: 375.0, Width: 750.0, Height: 50.0}
	mouseOnText := false

	framesCounter := 0

	rl.SetTargetFPS(24)

	for !rl.WindowShouldClose() {
		if rl.CheckCollisionPointRec(rl.GetMousePosition(), textBox) {
			mouseOnText = true
		} else {
			mouseOnText = false
		}

		for i := 1; i <= Size; i++ {
			//toPrint[i-1] = string(61 + i)
			x := (last_msg - i)
			if x < 0 {
				x += Size
			}
			toPrint[i-1] = messages[x%Size]
		}

		if mouseOnText {
			rl.SetMouseCursor(rl.MouseCursorIBeam)

			key := rl.GetCharPressed()

			for key > 0 {
				if (key >= 32) && (key <= 125) && (len(name) < 30) {
					name = name + string(key)
				}

				key = rl.GetCharPressed()
			}

			if rl.IsKeyPressed(rl.KeyBackspace) {
				if len(name) > 0 {
					name = name[:len(name)-1]
				}
			} else if rl.IsKeyPressed(rl.KeyEnter) {
				_, err := conn.Write([]byte(name + "\n"))
				if err != nil {
					fmt.Println("Błąd przy wysyłaniu wiadomości:", err)
					os.Exit(3)
				}
				name = ""
			}
		} else {
			rl.SetMouseCursor(rl.MouseCursorDefault)
		}

		if mouseOnText {
			framesCounter++
		} else {
			framesCounter = 0
		}

		rl.BeginDrawing()

		rl.ClearBackground(rl.White)

		rl.DrawRectangle(25, 25, 750, 325, rl.Black)

		//for j := 0; j < Size; j++ {
		//	rl.DrawText(toPrint[j], 30, int32(25*Size-j), 20, rl.White)
		//}

		rl.DrawText(toPrint[0], 30, 325, 20, rl.White)
		rl.DrawText(toPrint[1], 30, 300, 20, rl.White)
		rl.DrawText(toPrint[2], 30, 275, 20, rl.White)
		rl.DrawText(toPrint[3], 30, 250, 20, rl.White)
		rl.DrawText(toPrint[4], 30, 225, 20, rl.White)
		rl.DrawText(toPrint[5], 30, 200, 20, rl.White)
		rl.DrawText(toPrint[6], 30, 175, 20, rl.White)
		rl.DrawText(toPrint[7], 30, 150, 20, rl.White)
		rl.DrawText(toPrint[8], 30, 125, 20, rl.White)
		rl.DrawText(toPrint[9], 30, 100, 20, rl.White)
		rl.DrawText(toPrint[10], 30, 75, 20, rl.White)
		rl.DrawText(toPrint[11], 30, 50, 20, rl.White)
		rl.DrawText(toPrint[12], 30, 25, 20, rl.White)

		rl.DrawRectangleRec(textBox, rl.LightGray)
		if mouseOnText {
			rl.DrawRectangleLines(int32(textBox.X), int32(textBox.Y), int32(textBox.Width), int32(textBox.Height), rl.Red)
		} else {
			rl.DrawRectangleLines(int32(textBox.X), int32(textBox.Y), int32(textBox.Width), int32(textBox.Height), rl.DarkGray)
		}

		rl.DrawText(name, int32(textBox.X)+5, int32(textBox.Y)+8, 40, rl.Maroon)

		if mouseOnText {
			if len(name) < 30 {
				if ((framesCounter / 20) % 2) == 0 {
					rl.DrawText("_", int32(textBox.X)+8+rl.MeasureText(name, 40), int32(textBox.Y)+12, 40, rl.Maroon)
				}
			}
		}

		rl.EndDrawing()
	}
}
