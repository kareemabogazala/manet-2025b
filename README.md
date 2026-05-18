# MANET — Location-Based Routing for a Phone Ad-hoc Network

A **Mobile Ad-hoc Network (MANET)** built from ordinary Android phones. Phones discover each other directly, share their physical locations, and automatically forward messages through the shortest physical path — no router, no internet, no manual pairing.

---

## Motivation

In many real-world settings — disaster areas, agricultural fields, large warehouses, off-grid sensor deployments — there is no Wi-Fi or cellular infrastructure to rely on, yet devices still need to communicate with each other. Traditional routing protocols were designed for networks where nodes move constantly, which makes them complex and inefficient for the much more common case of **mostly stationary devices**.

We want to show that, for a largely static network, a simpler and more efficient routing approach is possible: instead of relying only on connectivity, use the **physical distance between devices** as the cost of each link, and pick the path that minimizes total physical distance. The result is a protocol that is easier to reason about, naturally adapts when a device occasionally moves, and can be demonstrated on ordinary Android phones acting as IoT-like nodes.

---

## Core Features

These are the features that deliver the project's main value. They must all work in the live demo.

- [ ] Phones automatically discover other phones running the app, with no manual pairing.
- [ ] Each phone determines its own location and shares it with the phones around it.
- [ ] Each phone shows a live list of the other phones it can reach and how far away each one is.
- [ ] A user can pick a destination phone and send a short text message to it.
- [ ] Messages are delivered even when the destination is not directly reachable, by automatically hopping through one or more intermediate phones along the shortest physical path.
- [ ] Each phone shows a simple on-screen log of the messages it sends, receives, and forwards.
- [ ] When a phone is moved to a new location, the other phones notice, update their view of the network, and start delivering messages to its new position.
- [ ] When the current path between two phones becomes unavailable (for example because a middle phone was moved away), messages are automatically re-routed through a different path.
- [ ] For each delivered message, the app shows the exact sequence of phones the message passed through.
- [ ] The app keeps running and stays connected to the network even when the phone's screen is off.
- [ ] The app recovers gracefully from short wireless glitches, so a momentary connection drop does not require restarting the demo.

---

## Complementary Features

These features add significant value and polish, and will be tackled after the core is working reliably.

- [ ] Each phone can be given a friendly, human-readable name that the other phones display.
- [ ] The app is smart enough to distinguish a real move from harmless location noise, avoiding unnecessary updates.
- [ ] A simple visual map shows all active phones and highlights the path used for the most recent message.
- [ ] Small files or images (not only text) can be sent across the network.
- [ ] The app reduces its power usage while the phone is stationary, so a long demo does not drain the battery.