## Location-Based Routing for a Phone Mesh Network

**Course:** 236272 — Project in Android Development, Spring 2025/26
**Sub-team:** Full team — Android implementation (2 students) + Simulation (1 student)
**Capacity:** Android: 2 students × ~6 h/week × 12 weeks ≈ **144 h** · Simulation: 1 student × ~6 h/week × 12 weeks ≈ **72 h**

> Each card is a user story, written in the functional template
> *"As a [USER] I want to [ACTION] so that [BENEFIT]"*.
> Cards are ordered top-to-bottom by importance inside each column.
> Hour estimates and owners are internal notes for the Sprint Planning meeting — they are **not** part of the GitHub card text.
>
> *Note:* Simulation stories (S1–S8) are owned by the Simulation engineer and are included in this backlog under each sprint. Android stories (1–13) are owned by the Android pair.

---

## Personas used in this backlog

| Persona | Who they are |
|---|---|
| **Device owner** | A person holding one of the phones that participates in the network. |
| **Demo presenter** | A team member presenting the working system at the project fair. |
| **Network observer** | A mentor / evaluator watching the demo and judging whether routing actually works. |
| **Simulation engineer** | The team member building and running the C++ simulation to validate the algorithm and produce comparison benchmarks. |

---

## Column 1 — Sprint 1 (Weeks 1–5) · *MVP — "Working beats perfect"*

**Sprint goal:** Three phones can find each other, share where they are, and successfully pass a short message from one phone to another — *including a case where the message has to travel through a middle phone*.

| # | User story (paste this text into the GitHub card) | Owner | Est. hours |
|---|---|---|---|
| 1 | **As a device owner**, I want the app to ask for and remember the permissions it needs (location and nearby-device access), so that the system can start working without me reconfiguring it every time. | Android-A | 4 |
| 2 | **As a device owner**, I want my phone to automatically detect other nearby phones running the same app, so that I do not have to manually pair or connect to any of them. | Android-A | 14 |
| 3 | **As a device owner**, I want my phone to know its own approximate location and share it with the phones it has discovered, so that the network knows where everyone is. | Android-B | 10 |
| 4 | **As a device owner**, I want to see the list of phones currently reachable from mine and how far away each one is, so that I can confirm the network sees them correctly. | Android-A | 8 |
| 5 | **As a demo presenter**, I want to pick a destination phone from a list and send a short text message to it, so that I can prove the system actually delivers messages/////. | Android-B | 8 |
| 6 | **As a demo presenter**, I want a message I send to reach its destination even when the destination is not directly reachable, by passing through one or more middle phones automatically, so that the core idea of the project is demonstrated////. | Android-A + B | 16 |
| 7 | **As a network observer**, I want each phone to display the messages it sends, receives, and forwards in a simple on-screen log, so that I can follow what is happening during the demo without external tools. | Android-B | 6 |
| S1 | **As a simulation engineer**, I want to model each phone as a C++ `Node` with a GPS position and communication range, and automatically build a network graph where two nodes are connected if they are within range (edge weight = physical distance), so that the simulation has a realistic network to run on. | Sim | 8 |
| S2 | **As a simulation engineer**, I want to run a working end-to-end routing algorithm on the graph, trace each hop from source to destination, and verify the correct path on a known test case, so that the pipeline is confirmed correct before the real algorithm is introduced. | Sim | 6 |
| S3 | **As a simulation engineer**, I want a pluggable algorithm interface so that I can swap any routing algorithm — location-based Dijkstra or a baseline — and run them on the same network without touching the simulation core. | Sim | 6 |
| S4 | **As a network observer**, I want to see a side-by-side comparison of path distance and hop count between location-based Dijkstra and the baseline on the same scenario, so that there is early proof the algorithm performs as expected. | Sim | 5 |

**Sprint 1 total:** ≈ **91 h** · Android: ≈ 66 h (≈ 33 h/student) · Simulation: ≈ 25 h · fits in 5 weeks at 6 h/week.

---

## Column 2 — Sprint 2 (Weeks 6–11) · *Mobility, robustness, and demo polish*

**Sprint goal:** The network reacts correctly when a phone is moved to a new place, recovers from short connection problems, and the app is robust enough for a live demo in front of mentors.

| # | User story | Owner | Est. hours |
|---|---|---|---|
| 8 | **As a device owner**, I want my phone to announce to its neighbors when I have moved noticeably far from where I was, so that the others stop trying to reach me at my old location. | Android-A | 10 |
| 9 | **As a device owner**, I want my phone to re-introduce itself to the network once I have stopped at a new place, so that messages can start reaching me at my new location. | Android-A | 8 |
| 10 | **As a demo presenter**, I want messages to be re-routed through a different path when the current path becomes unavailable, so that the demo keeps working even if one phone is moved or temporarily disconnected. | Android-B | 14 |
| 11 | **As a network observer**, I want to see, for each delivered message, which phones the message actually passed through, so that I can verify the routing decision was sensible. | Android-B | 8 |
| 12 | **As a device owner**, I want the app to keep running and stay connected to the network even when its screen is off, so that the demo does not break when a phone is set down. | Android-A | 12 |
| 13 | **As a demo presenter**, I want the app to recover gracefully if one phone briefly loses its wireless link, so that small glitches during the live demo do not require restarting everything. | Android-B | 8 |
| S5 | **As a simulation engineer**, I want to move a node beyond its radius during a running scenario and have the graph automatically drop and rebuild its edges, and measure how many edges changed and how long re-routing took, so that I can quantify the cost of device movement on the network. | Sim | 8 |
| S6 | **As a simulation engineer**, I want to run the same experiment across multiple network sizes (10, 50, 100 nodes) and device densities and collect path distance and hop count per run, so that I can show how both algorithms scale and where the difference grows. | Sim | 8 |
| S7 | **As a simulation engineer**, I want to export all experiment results to a CSV file, so that results are reproducible and can be reviewed or re-plotted by anyone on the team. | Sim | 4 |
| S8 | **As a network observer**, I want to run the simulation with a single command and see a printed summary comparing location-based Dijkstra against the baseline — including best case, worst case, and key tradeoffs — so that the algorithm's value is immediately clear at the project fair. | Sim | 8 |

**Sprint 2 total:** ≈ **88 h** · Android: ≈ 60 h (≈ 30 h/student) · Simulation: ≈ 28 h · leaves ~12 h per student in Week 12 for integration testing, final polish, and demo preparation.

---

## Column 3 — Nice to Have (only if time permits)

| # | User story | Tentative owner |
|---|---|---|
| 14 | **As a network observer**, I want to see a simple visual map of all the phones and the path a message took between them, so that the routing is easy to follow at a glance. | Android-B |
| 15 | **As a device owner**, I want the app to be smarter about deciding when I have "really moved" versus when my location reading just fluctuated, so that the network is not disturbed by harmless noise. | Android-A |
| 16 | **As a device owner**, I want to give my phone a friendly name shown to the others, so that the demo is easier to follow than reading raw identifiers. | Android-B |
| 17 | **As a demo presenter**, I want to send small files or images (not only text) through the network, so that the demo is more impressive to visitors. | Android-A + B |
| 18 | **As a device owner**, I want the app to use less battery when nothing is moving, so that a long demo does not drain the phones. | Android-A |

---

## Internal notes (NOT shown on the GitHub cards — for the Sprint Planning meeting)

### Technologies under consideration

**Android side:**
- **Peer-to-peer link:** Google Nearby Connections API (primary candidate — abstracts Wi-Fi + Bluetooth, simplest for a 3-phone demo). Wi-Fi Direct as fallback.
- **Location:** Android FusedLocationProvider (Google Play Services).
- **Foreground service** to keep the app alive when the screen is off (story #12).
- **Language / framework:** Kotlin + Android Jetpack.

**Simulation side:**
- **Language:** C++17 with CMake build system (chosen for performance and low-level control as the student's final Technion project).
- **Core data structures:** Custom `Node` class (GPS position + range), `Graph` class with adjacency list (edges = physical distances), `IRoutingAlgorithm` pluggable interface.
- **Algorithms registered:** `LocationDijkstra` (our proposal) + baseline TBD (hop-count Dijkstra or flooding).
- **Output:** Console comparison + CSV export of results per experiment run.
- **Build:** `cd simulation/build && cmake .. && make` → `./bin/simulation`

### Top risks
1. **Modern Android randomizes MAC addresses** — identifying devices reliably must use an app-generated ID, not the MAC.
2. **GPS accuracy is poor indoors** (~5–10 m error). Demo distances and the motion-radius threshold must be larger than this error margin.
3. **Background-execution restrictions** on recent Android versions can kill the app — addressed by story #12 (foreground service).
4. **Peer-to-peer link instability** during handshakes — addressed by stories #10 and #13.
5. **Baseline algorithm not yet defined** (simulation) — must be agreed on by the team before S4 is complete, so the comparison is fair and meaningful.
6. **Simulation assumptions must stay in sync with the Android implementation** — if the Android team changes how location or edge costs are calculated, the simulation parameters must be updated to match.

### Responsibility split
- **Android-A:** discovery, location sharing, mobility detection, lifecycle / foreground service.
- **Android-B:** UI, message send/receive, multi-hop forwarding logic, path display, recovery.
- **Sim:** C++ simulation — network modeling, algorithm engine, mobility experiments, CSV export, comparison report.
- Story #6 (multi-hop) is intentionally shared between Android-A and Android-B — it is the integration point of the two halves.

### Sprint-level definition of done
- **Sprint 1:** a live demo on 3 physical phones where a message from phone A reaches phone C through phone B, with the route visible on screen. Simulation produces a working end-to-end routing result and a basic side-by-side comparison against the baseline.
- **Sprint 2:** same Android demo, plus moving phone B causes the network to re-route within a few seconds, and the app survives a screen-off and a brief link drop without restart. Simulation produces CSV results and a final comparison summary across multiple network sizes and densities.
