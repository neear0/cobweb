🕸️ Cobweb – SSH Honeypot in C++

Cobweb is a modular SSH honeypot written in pure C++ (no Python bloat) designed to silently lure and log unauthorized SSH access attempts. It's ideal for cybersecurity research, threat intelligence, or just catching curious scanners.

🧠 Built from scratch in C++ for full transparency and performance

🧼 Clean object-oriented structure (c_server, c_connection_handler)

📡 Accepts and logs all incoming TCP connections (default port: 2222)

🎭 Sends fake SSH banner (OpenSSH_7.9p1) to simulate a real server

📥 Captures raw input from attackers (credentials, probes, etc.)

💻 Cross-platform support (Windows & Linux, thanks to conditional compilation)
