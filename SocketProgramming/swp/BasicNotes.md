## Stop and Wait

<img style="height:300px;width:350px" src="https://media.geeksforgeeks.org/wp-content/uploads/Stop-and-Wait-ARQ.png">

* Sends <b>1 packet</b> and wait for the confirmation from the reciever of that <b>1 packet</b>.
* Since only 1 packet is send and recived the window size of sender and reciever is equal to 1.
* Least efficient of all as only 1 packet is sent
  
  ## Go Back N
  
<img style="height:300px;width:450px" src="https://www.geeksforgeeks.org/wp-content/uploads/Sliding_SET_2-1.jpg">

  * Here multiple packets are sent to the reciever by the sender and the reciever sent a single acknowledgment for all of them.
  * It is efficient than Stop and wait but the problem is the reciver window size is 1.

    That is if `[1] [2] [3]` are sent from the sender in order and `[1]` is lost, even if `[2]` and `[3]` reached the reciver the reciver won't accept it as it is waiting for the `[1]`
    hence it has to recent all the elements again from `[1]` that is `[1] [2] [3]`.
    
  * A major disadvantage of this is obviously excessive retransmission of packets.

  ## Selective Repeat

  <img style="height:350px;width:450px" src="https://www.tutorialspoint.com/assets/questions/media/59904/15.jpg">
  
  * Solves the problem in Go Back N ie it retransmits only those packets that have been lost. That is why it is called " selective Repeat "
  * Most Efficient among the three sliding window protocols
    
