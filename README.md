
# 🗨️ TCP Talk - Simple Terminal Chat App

**TCP Talk** is a simple client-server chat application built using low-level socket programming in C. It enables two users (client and server) to exchange messages in real time through a TCP connection using the terminal.

---

## 📌 Features

- 📡 Socket-based communication using TCP 
- 🧑‍💻 Real-time, two-way message exchange
- 🖥️ Terminal-based interface (CLI)
- 🔒 Graceful termination with `"bye"`
- 🧪 Great for learning network programming in C

--- 



## 🛠️ Requirements

- GCC Compiler
- Linux or UNIX-based system
- Basic knowledge of C and networking

---

## 🚀 How to Run

### 1. Compile both programs

```bash
gcc server.c -o server
gcc client.c -o client
````

### 2. Run the server

```bash
./server
```

### 3. Run the client (in a different terminal)

```bash
./client
```

> ✅ Once connected, you can send messages from both terminals.
> 🛑 Type `bye` to terminate the chat session.

---

## 🧠 How It Works

* **Server:**

  * Creates a socket
  * Binds to port `8000`
  * Listens for incoming connections
  * Accepts the client and exchanges messages

* **Client:**

  * Connects to the server at `127.0.0.1:8000`
  * Sends and receives messages using `write()` and `read()`

* Both terminate the session when either side types `bye`.

---

## 🖼️ Sample Output

**Client Terminal:**

```
Connected to server
Hello Server!
Server: Hello Client!
bye
```

**Server Terminal:**

```
Client: Hello Server!
Client: bye
```

---

## 📚 Concepts Covered

* `socket()`, `bind()`, `listen()`, `accept()`, `connect()`
* `read()` and `write()` for message I/O
* TCP socket setup in C
* Server-client architecture

---

## 🏁 Future Improvements

* Multi-client support using `fork()` or `select()`
* Message timestamps
* Message encryption
* GUI using GTK or ncurses

---


