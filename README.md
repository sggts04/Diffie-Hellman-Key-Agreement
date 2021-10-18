## Diffie-Hellman Key Agreement

### Run locally
For compilation, the miracl library has been used. The compiled `.a` file and header files have been included but in case they don't work for your system. [Please follow this guide to install miracl yourself.](https://adityagudimetla.medium.com/installing-miracl-for-dummies-7eb7192c3285)

```bash
gcc server.c -o server -I ./include libmiracl.a
gcc client.c -o client -I ./include libmiracl.a
```
Then run `./server` and `./client` on two separate terminals.

### Walkthrough

We have implemented a client-server setup where the client acts as Alice, and server acts as another person Bob. Both of them know the public part of the key `p`, it has been pre-defined in the code as large 1024 bit prime but can be easily changed.

Now we start running our server and the client attempts to connect to it.

Client Process (Alice):

![](https://raw.githubusercontent.com/sggts04/Diffie-Hellman-Key-Agreement/master/screenshots/Alice-1.PNG)

Server Process (Bob):

![](https://raw.githubusercontent.com/sggts04/Diffie-Hellman-Key-Agreement/master/screenshots/Bob-1.PNG)

Now, just press enter on the Client(Alice) terminal to initiate the process.

Alice generates a 160 bit random number `a` and uses it to generate `Pa = p^a`. Then sends it to Bob.

Bob recieves `Pa` and at the same time, Bob generates a 160 bit random number `b` and uses it to generate `Pb = p^b`. Then sends it to Alice.

Then Alice and Bob use these to find the common key.

For Alice: `Key = Pb^a`

For Bob: `Key = Pa^b`

Client Process (Alice):

![](https://raw.githubusercontent.com/sggts04/Diffie-Hellman-Key-Agreement/master/screenshots/Alice-2.PNG)

Server Process (Bob):

![](https://raw.githubusercontent.com/sggts04/Diffie-Hellman-Key-Agreement/master/screenshots/Bob-2.PNG)

As you can see, Alice and Bob have managed to achieve the same common key without using a KDC.
