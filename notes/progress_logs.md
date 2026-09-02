Progress log 1 of electronics:
I watched the entire first video of the Ben Eater 6502 computer from 0. I connected the 6502 CPU to the breadboard, and saw the outputs of the address bus with an Arduino. (I haven't fully built the clock and connected it to the CPU, so currently I just use a button for this with single ticks.) Also I learned about interrupts, the data bus and the basic looping function of the CPU (I think).

Progress log 2:
I opened up the EEPROM chip, and connected it into a NAND gate in order to make it work with the CPU only in the range that fits with the EEPROM (15 bits). Also I learned the basics of how EEPROM works, and also tested if the NAND gate chip works.

Progress log 3:
Organized most of the cables, only 3 left to organize.

Progress log 4:
I organized the final 3 remaining cables (Ben Eater style) which was relatively hard and took a decent amount of time. Then I tested the Arduino and found a bug: the CPU was outputting straight 0's on the address bus. I fixed this bug by fixing the reset button's wiring. Currently I am trying to fix a new bug and understand why after a restart the CPU doesn't start like it should.

Progress log 5:
Fixed the reset program not working properly bug. A few things fixed it:
First of all, some CPU pins didn't get enough power because they were connected through the 3.3 V power source of the Arduino. I figured this out by making a debug file, which is simple. It only checks and reads the analog value of a certain pin of the Arduino, so I connected the cable and debugged this way.

Also, using GPT, I realized part of the reason that the logs of the recent program counter didn't seem correct is because of button bouncing. I fixed the button bouncing by making the button digital.

Overall, I am happy with the consistency so far. But things are moving slowly. Tomorrow I want to put in like four hours because it's the weekend. I want to start by organizing the cables a bit, because stuff got a little bit messy. Also I want to connect the EEPROM to the CPU and completely finish part 2 of the series.

Progress log 6:
Connected the address bus and the data bus of the EEPROM and CPU together (this took a lot of time because of all of the wires).

Progress log 7:
Uploaded the basic EA program to the EEPROM, and it worked (I verified by reading the data bus pins of the CPU). It took me like an hour to upload the program because I misread the XG Pro programmer's output and didn't understand the correct orientation for the chip. I kept asking AI what the problem was because I assumed it wasn't the software, when the software had already told me exactly what I needed to do. This really makes me think I need to be careful using AI tools for learning in general. I think it's good, especially in learning, to only ask good questions. When I say good questions, I'm talking about the hacker-style article about asking good questions. That's the only kind of question you should ask while learning, and probably in general with current AI, in order to not get atrophied — because this was just brain atrophy.

Now I changed the EA program a bit. The change was that in the reset sequence I changed the last two values of the reset vector in the EEPROM. For some reason I can't read it with the Arduino. I need to fix this! My plan is to:

1. First of all, get my RAM up to date to know everything works.
2. Check all of the connections and the code.
3. If it doesn't work, give all of the context to an AI and ask it a good question and try to figure it out this way.

Overall, I am happy that I put in the two hours today, but the progress is really, really slow. I only log the days when I am working — there were three that I didn't because of the army, and I finish at 9 each day starting from 7, so yeah, I need to move much faster.

Progress log 8:
Debugged all day. At the end of the two hours realized it was probably the clock pin not connected. Arduino probably burned, will continue later.

Progress log 9:
There was a short and the Arduino didn't turn on. I tried to figure out why for some time and didn't find it, so I disconnected and reconnected everything, and then the short stopped shorting, I guess. It took the whole day because it takes time to connect and disconnect everything.

Progress log 10:
Switched to organized wires because it was messy as hell.

Progress log 11:
Readings weren't correct. I got "aaa" instead of "ea" from the data bus of the CPU. Also, I accidentally wired the Ben Eater style wires above the EEPROM, so I couldn't get it out, which is a problem because I need to repeatedly take it out and program it with the EEPROM programmer. So, for the 100th time, I took out all of the wires again, because the wires above the EEPROM were at the bottom, and I wired everything up again with no wires above the EEPROM. Then I checked everything (with the debug file) and everything works except the CE pin, which I will fix tomorrow. (For the check, I just hard connected it to ground since I saw it's not low at the beginning for some reason.) Also I started working on the GitHub and GitHub workflow today since I realized it's important. Also: short cables first, always, in the wiring!

![[Pasted image 20260701142458.png]] explain about this

Progress log 12:
After checking some wires with the Arduino analog rig, because I don't have a multimeter, I realized the problem was that the NAND gate wasn't working, even though it got 2 signals as input it still outputted one. After further checking, I realized this was because one of its pins was bent and not connected to the breadboard — specifically the GND one. Using pliers, I fixed the pin's angle. Here is the NAND gate, and now everything worked.

Progress log 13:
Progressed like 11 min through the video. Made some Ben Eater style wires in order to have some extra short breadboard wires. Learned about the 65C22 interface chip and the NAND gate configuration.

Progress log 14:
Finished the part two video.

Progress log 15 (halfway):
Connected all of the LEDs to the data bus of the interface chip. The interface chip did make the LEDs light up and acted as I thought, but instead of looping over and over again it just returned to reading EAs after the initial LED light up. I wanted to fix this fast, so I wrote a detailed prompt with all of the details to Claude Fable 5. It suggested stuff to check, and after a decent amount of time it worked. I'm actually not sure what happened. I think there was a broken wire, or two wires touched each other, which may have caused the problem. At the end, I made 8 new Ben Eater style wires to start tightening up the whole thing, and tomorrow I want to finish tightening up, which should take a lot of time. Also, I want to summarize everything and get a better world model of the system in my head, because right now it's a bit fuzzy. That's it.

Progress log 16 (only like 30 min):
Fixed a bad wire connected to the EEPROM and started summarizing the old system, writing an entire system architecture to understand stuff better. It really seems like it's pretty simple if you look a little bit higher up, from an inputs and outputs perspective.

Progress log 17 (only 1 hour and 15 min because I came back from the IDF):
Wrote the system overview and organized two long cables Ben Eater style. I need to remember tomorrow to make the point of the white cable a little longer, and I also need to continue the organization a bit with a few more long cables.

In the next session:
Finish organizing a few more cables. Don't overdo it! Maybe decide which cables you want to organize at the start, to not be too OCD and clean about it. Also, you obviously don't want to make it too messy. Also, watch the video. It's only an explanation video without actually doing anything. Maybe summarize it if there is something.

Progress log 18:
Organized wires, loaded my RAM because I haven't done anything in a while because of the IDF. At the end of the session, a new bug I will fix tomorrow.

Progress log 19:
Loaded my RAM, which took a while again because I haven't had time to work on this because of some things. Fixed the bug from the previous session (turns out the reset pin of the interface chip wasn't connected to the reset button correctly).

Tomorrow:
1. Finish organization
2. Watch part 3 video

Progress log 20:
I downloaded an assembler called "vasm", and I wrote assembly code to do what I did before I added the assembler. I also commented on the code carefully to understand what it does. Also, I watched the entire part 3 video. Tomorrow I'm excited to start actually connecting the thing to a screen.

Progress log 21:
Started part 4! Connected and turned on the LCD screen, and the contrast setting is working.

Progress log 22:
Finally finished part 4! Hello world on the screen is working! I started the session by connecting the LCD interface pins into port B of the interface chip and part of port A. Then I watched the video and understood the basic premise and the code. Then I copied the vasm code, uploaded it to the EEPROM using the programmer, plugged the EEPROM back in again, and the Hello world program worked.

In the next session I need to:
* Refresh my understanding of the code and the system in general (and update the summary with untouched parts). Make sure I revisit the address range concept at the low level.
* Organize the LCD to interface data line cables Ben Eater style.
* I will forget all the extra documents that were not saved on the PC, like the LED linking stuff and the first macro. Don't make everything organized yet — just save them somehow so I remember them in the future when I make everything look nice.

Progress log 23:
I replaced the original messy wires with Ben Eater style ones between port B and the LCD screen. I had a bug where the screen didn't work. It was stupid! I realized the mistake was that I forgot to connect parts of port A into the LCD screen (why do I need port A?). Then I read all the computer architecture notes and started to load my RAM with everything again. I feel like I don't have as good an understanding as I used to.

Progress log 24 (1 hour):
I was kind of not ready to move to the next video because I feel like I don't fully understand the system. I think this is due to the code itself and to the interface chip, so I started reading the code again, which is now clearer. I also have GitHub with everything in one place.

Progress log 25 (1 hour):
Spent the first 40 minutes loading up my RAM because something about the system didn't seem clear to me. I realized it was the interface chip and the LCD, and the extra LCD pins that are connected through the interface chip on the last three port A pins. So I wrote a summary for the interface chip and understood how it works better. I also did that for the LCD. I talked and asked questions about both of them and summarized with GPT. Also, I progressed 8 minutes through the part 5 video.

Progress log 26:
Watched the entire part 5 video about the stack, then I wrote a summary about the stack. After I wrote the initial summary, I gave it to GPT and asked it to refine it. It did a pretty good job, and I just copied the summary — but I think this offloads a lot of the understanding. From now on, I want to write the summary completely on my own with good wording and language, and then I can ask GPT for refinement without copying and pasting: just add refinements on my own or change the text on my own. I think asking it to refine the summary, copying it, and calling the new, better summary mine is not going to work for actually understanding stuff well.

Progress log 27:
Started connecting the RAM chip and made 14 Ben Eater style wires, which took a while.

Progress log 28 (45 minutes):
Connected the RAM to the rest of the board except its chip select and output enable pins.

Progress log 29:
After the new RAM installation and the new Hello world code, the program didn't work, so I started debugging. First of all, I rechecked a lot of the connections, and then I got the EEPROM out. I put in the old Hello world program without the subroutines, removed the RAM, and checked if everything works. It does work, which means the RAM connection is the problem. Now I'm going to recheck whether the logic that activates the RAM's pin works, or whether it's the address/data bus (in the next session).

Progress log 30 (1 hour):
More debugging. Seems to be the data bus.

Progress log 31:
More debugging. The problem seems to be the address bus connection. While debugging, I created a new problem with the connection between the 65C22 interface chip and the LCD. I need to fix that tomorrow and organize everything before I can actually work on the address bus from the EEPROM to the RAM, and only then can I fix it. The system should work, and I should finish with this thing.

Progress log 32 (soldering horror day 👿):
One of the EEPROM chip's leg pins was ruined, so I bought solder and tried to solder it, but accidentally removed the exposed metal part completely. I ordered a new chip on eBay, which unfortunately would arrive in 10 days.
