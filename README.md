# p2pchatc
P2pchat in C

#Not Done yet

#idea
influenced by: http://icai.ektf.hu/pdf/ICAI2007-vol1-pp193-201.pdf
a p2p protocol designed as a cellular automaton
Every peer has its neighbors (moore) and its bootstrapping procedure is dependend on its 8 neighbors.
Aswell as messages will be distributed from neighborhood to neighborhood

What is done?
- [x] Linked-List Peers
- [x] Receive Message
- [x] Add Peers with random generated String (current pseudo hash)
- [ ] Actual SHA Hashing algorithm
- [ ] Hashed Messages
- [ ] Broadcast for lan (Bootstrapping)
- [ ] Peer Exchange
- [ ] End-To-End Encryption preferably AES
- [ ] Sending Messages
