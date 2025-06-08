
# Eventloop for Embedded Systems

**A lightweight Event Loop framework written in C++98, designed for Embedded Systems.**

This event loop is designed to efficiently monitor and manage user events (such as keypad, touchpad, etc.) in resource-constrained environments.  
It utilizes a dedicated thread to continuously check and process events in a thread-safe manner, making it suitable for real-time or interactive embedded applications.
This eventloop is useful when you can not directly use unix file descriptors to pull events(select(), poll(), epoll(), ...); for example consider there are APIs for checking hardware IO.

---

## ✨ Features

- Event loop implemented using **C++98** and **POSIX threads (pthreads)**
- Suitable for embedded platforms with limited resources
- **Thread-safe event queue management** with `pthread_mutex` and `pthread_cond`
- Implements **Singleton pattern** → only one event loop instance runs
- Supports:
  - Adding events dynamically
  - Removing events at runtime
  - Suspending/resuming event processing thread when no events are present
- **Low CPU usage** → thread suspends itself when no events exist

---

## 🗂 Architecture Overview

```plaintext
+------------------------+
|   Application Layer    |
| - User Events (keypad) |
| - Timer Events         |
+-----------+------------+
            |
            v
+-----------+------------+
|      Event Loop        |
| - Event List           |
| - Loop Thread          |
| - Append / Remove API  |
| - Suspend / Resume     |
+-----------+------------+
            |
            v
+-----------+------------+
|       Event Base       |
| - check() Method       |
| - Inherited by Events  |
+------------------------+
```

---

## 🛠 How It Works

1. `Eventloop` is initialized using `Eventloop::init()`.
2. It creates a background thread (`loopThread`) that continuously monitors the list of events.
3. Events implement a `check()` method, which is called periodically.
4. If no events are present → the thread suspends itself to save CPU.
5. When a new event is appended → the thread is resumed and starts processing events.
6. You can remove events at any time.

---

## 🚀 Example Usage

```cpp
Eventloop::init();
Eventloop *loop = Eventloop::getInstance();

// Example: Adding an event
Event *myEvent = new MyCustomEvent();
loop->append(&myEvent);

// Example: Removing an event
loop->remove(&myEvent);
```

---

## 🔍 Key Components

| Component | Description |
|-----------|-------------|
| `Eventloop` | Singleton Event Loop manager |
| `loopThread` | Background thread for event checking |
| `eventList` | Thread-safe list of active events |
| `append()` | Add new event |
| `remove()` | Remove event |
| `suspendThread()` | Suspend loopThread when no events exist |
| `resumeThread()` | Resume loopThread when new event is added |
| `Event` | Abstract base class, requires `check()` method implementation |

---

## 📝 Design Notes

- Designed with **Embedded constraints in mind**:
  - Small code footprint
  - Thread-safe operation
  - Efficient resource usage
- Written in **C++98** to ensure compatibility with older embedded toolchains.

---

## 📚 Example Scenario

This Event Loop can be used to manage:

✅ User interface input (keypad / touchpad)  
✅ Timers / periodic tasks  
✅ Communication events (UART/USB status)  
✅ Sensor state monitoring

---

## 🧑‍💻 Author

Pouya Imani → [GitHub Profile](https://github.com/pouyaimani)

---

## 📜 License

[MIT License](LICENSE)
