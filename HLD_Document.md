# TCP client-server secure chat app

## 1. Introduction about the chat app 

**Objective**: To develope a secure TCP-based chat application that supports multi-user communication with group chat functionality, chat history storage, and encryption using OpenSSL 
**Target platform**: Ubuntu 22.04 (64-bit)
**Communication mode**: Chat Room - all users can se and send message in onme shared room
**Security**: All data transmissions are protected using SSL

---

## 2. Functional requirements 

- Allow users to register (by enter *Username* and *Password*) and login
- All the history os chat room will be stored
- Support for multiple concurrent users
- Group chat: messages are broadcast to all connected clients
- Persist all user data, sessions and chat logs after restarting the server or client

---

## 3. Non-functional requirements

- **Security**: SSL encryption via OpenSSL.
- **Concurrency**: Multi-threaded server can handle multiple clients simultaneously.
- **Persistence**: Data is preserved across server restarts.
- **Portability**: Only standard C and OpenSSL libraries are used.
- **Ease of deployment**: Includes Makefile for build automation.

---

## 4. System context diagram

+-------------+ TCP over SSL +-------------+ Thread
| Client 1 | <========================> | | +---------+
| (Ephemeral) | | | <=> | Thread 1 |
+-------------+ | Server | +---------+
+-------------+ | (Port 4443)| +---------+
| Client 2 | <========================> | | <=> | Thread 2 |
+-------------+ +-------------+ +---------+
|
+--------------+
| Broadcast Msg |
+--------------+

---

## 5. High-level module description  

| Module           | Description |
|------------------|-------------|
| `server/main.c`  | Sets up SSL context, listens for clients, and handles multi-threaded communication. |
| `client/main.c`  | Connects to server, manages user input/output, and displays chat messages. |
| `auth.c`         | Manages login and registration logic. |
| `session.c`      | Generates and validates session tokens. |
| `chat.c`         | Formats messages and broadcasts to all connected clients. |
| `ssl_utils.c`    | Handles SSL/TLS handshake and data transmission. |
| `storage.c`      | Reads/writes user info, session data, and chat logs. |

---

## 6. Data and file design

| File | Purpose |
|------|---------|
| `users.db` | Stores username and hashed password. |
| `sessions.db` | Maps session tokens to usernames. |
| `chat_history.txt` | Stores group chat logs in format: `[timestamp] username: message`. |

---

## 7. Security design

- All communication between clients and server is encrypted using OpenSSL (SSL_read, SSL_write).
- Passwords are securely stored using hash functions with salt.
- Session tokens are randomly generated and stored in sessions.db.
- Even if intercepted via tools like Wireshark, data remains unreadable.

---

## 8. Tool and library


---

## 9. Limitations and enhancement


--- 
