package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

type Server struct {
	host string
	port string
}

type Client struct {
	conn net.Conn
}

var clients []*Client

func (server *Server) Run() {
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%s", server.host, server.port))
	names := [26]string{"ALFA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL", "INDIA", "JULIETT", "KILO", "LIMA", "MIKE", "NOVEMBER", "OSCAR", "PAPA", "QUEBEC", "ROMEO", "SIERRA", "TANGO", "UNIFORM", "VICTOR", "WHISKEY", "X-RAY", "YANKEE", "ZULU"}
	index := 0
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatal(err)
		}

		client := &Client{
			conn: conn,
		}
		clients = append(clients, client)
		go client.handleRequest(names[index%26])
		index++
	}
}

func (client *Client) handleRequest(name string) {
	defer fmt.Printf("Connection from: %s has been closed\n", client.conn.RemoteAddr().String())
	reader := bufio.NewReader(client.conn)
	fmt.Printf("New connection from: %s\n", client.conn.RemoteAddr().String())

	for {
		message, err := reader.ReadString('\n')
		if err != nil {
			client.conn.Close()
			return
		}
		fmt.Printf("Message incoming from %s: %s", name, string(message))
		for _, cl := range clients {
			// aby wysylac do wszystkich poza nadawca, nalezy dodac if cl != client 
			cl.conn.Write([]byte(name + ": " + string(message)))
		}
		time.Sleep(1)
	}
}

func main() {
	server := Server{"192.168.179.129", "8080"}
	server.Run()
}
