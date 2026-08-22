Progress log 1 of electronics:

I watched the entire first vid of ben eater 6502 computer from 0. I connected the 6502 cpu to the mother bored, and saw the outputs of the address buss with an Arduino. (I haven't fully built the clock and connected it to the cpu, so currently I just use a button for this with single ticks.) Also I learned about interrupts, data buss and the basic looping function of the cpu (I think).

Progress log 2:

I Opened up the EEPROM chip, and connected it into an NAND gate in order to make it work with the cpu Only in the range that fits with the EEPROM (15 bits). Also I learned about the basics Of how EEPROM works, and also tested if the NAND gates chip works.

Progress log 3:

Organized most of the cables only 3 left to organize.

Progress log 4:

I organized the final 3 remaining cables (Ben Eater style) which was relativity hard and took a decent amount of time. Then I tested the Arduino and found a bug the CPU was outputting stright 0's in the address buss I fixed this bug by fixing the reset buttons wiring. Currently I am trying to fix a new bug and understand why after a restart the cpu dosen't start like it should.

Progress log 5:

Fixed reset program not working properly bug. A few things fixed it:

First of all, some CPU pins didn't get enough power because they were connected through the 3.3 V power store of the Arduino. I figured this out by making a debug file, which is simple. It only checks and reads the analogue value of a certain pin of the Arduino, so I connected the cable and debugged this way.

Also, using GPT, I realised part of the reason that the logs of the recent programme counter didn't seem correct is because of button bouncing. I fixed the button bouncing by making the button digital.

Overall, I am happy with the consistency so far. But things are moving slowly. Tomorrow I want to put in like four hours because its weekend. I want to start by organising the cables a bit,  because stuff got a little bit messy. Also i want to connect the EEPROM to the CPU and completely finish part 2 of the series.

Progress log 6:

Connected the address buss, and the dataBuss of the EEPROM and CPU together (This took a lot of time because all of the wires).

Progress log 7:

Upload the basic EA program to the EEPROM, and it worked (I verified by reading the data buss pins of the cpu). It took me like an hour to upload the programme because of me being dumb and not understanding the correct position for the CPU. I continually asked AI what the problem is because I thought it wasn't the software and also didn't read carefully what the xg pro software outputted. It just explained exactly what I need to do. This really makes me think I need to be careful, and I already thought about it, using AI tools for learning in general. I think it's good, especially in learning, to only ask good questions. When I said good questions, I'm talking about the article, the hacker-style article about the good question stuff. This is the only question you should ask while learning and also probably in general right now with current AI. In order to not get atrophied, because this was just brain atrophy. Now I changed the EA programme a bit. The change was that in the reset sequence I changed the last two pins of the reset sequence values in the eeprom. For some reason I can't read it with the Arduino. I need to fix this! My plan is to:

First of all, get my RAM up to date to know everything works.

Check all of the connections and the code.

If it doesn't work, give all of the context to an AI and ask it a good question and try to figure it out this way.

overall, I am happy that I put in the two hours today, but the progress is really, really slow! I just currently logged the days when I am working. There were three that I didn't because of the army, and I finish at 9 each day from 7, so yeah, I need to move much faster

Progress log 8:

Debugged all day, at the end of the two hours realized it was the clock pin not connected probably. arduino burned probably continue later

Progress log 9:

There was a short and the Arduino didn't turn on. I tried to figure out why for some time and didn't realise why, so I disconnected and connected everything, and then the short stopped shorting, I guess.  it took the whole day because it takes time to connect everything and disconnect.

Progress log 10:

Switched to orgenized wires because it was messy as hell.

Progress log 11:

readings weren't correct. I got "aaa" instead of "ea" from the data bus of the CPU .  also, I accidentally wired the Ben Ethersail wires above the EEPROM, so I couldn't get it out, which is a problem because I need to repeatedly take it out and programme it with the EEPROM programmer  so, for the 100th time, I took out all of the wires again because the wires about the EEPROM were at the bottom, and I wired everything up again. with no wires above the eeprom. The I checked evreything (with the debug file) and evreything works except of the ce pin which i will fix tommorow. ( for the check, I just hard connected it to ground since I saw it's not low at the beginning for some reason) Also i started working on the github and github workflow today since i realized its importent. Also short cabels first always in the wiring!!!!

Pasted image 20260701142458.pngexplain about this

Progress log 12:

After checking some wires with the Arduino analogue rig because I don't have a multimeter.  I realised the problem was the non-grid wasn't working, even though it got 2 signals as input. It still outputted one  after further checking, I realised this was because one of his pins was bent and not connected to the breadboard. Specifically, the GND one  using a plier, I fixed the pin's angle. Here is the NAND gate, and now everything worked.

Progress log 13:

Progressed like 11 min through the video. Made some ben eater style wires in Order to have some extra short bread board wires. Learned about the 650222 interface chip and the nand gate configuration.

Progress log 14 (Today):

Finished the part two video

Progress log 15 (Half way):

connected all of the LEDs to the data bus of the interface chip.  the interface chip did make the LEDs light up and acted as I thought, but instead of looping over and over again itjust returned to read EAs after the initial LED light up.  I wanted to fix this fast, so I wrote a detailed prompt with all of the details to Cloud Fable 5. It suggested stuff to check, and after a decent amount of time it worked. I'm actually not sure what happened. I think there was a broken wire or two wires touched each other that may have caused a problem.  at the end, I made 8 new beneter style wires to start tightening up the whole thing, and tomorrow I want to finish tightening up, which should take a lot of time. Also, I want to summarise everything and get a better world model of the system in my head, because right now it's a bit fuzzy. That's it.

Progress log 16 (only like 30 min):

fixed bad wire connected to the EEPROM and started summarising the old system, writing an entire system architecture to understand stuff better. It really seems like it's pretty simple if you look a little bit higher up and from an inputs and outputs perspective.

Progress log 17 (only 1 hour and 15 min cause i came back from idf ):

Wrote the system overview and organised two long cables Ben Eater style. I need to remember tomorrow to make the point of the white cable a little longer, and I also need to continue the organisation a bit with a few more long cables, OK.

in the nexrt session:

finish organising a few more cables. Don't overdo it! Maybe decide which cables you want to organise at the start to not be too OCD and clean about it. Also, you obviously don't want to make it too messy. Also, watch the video. It's only an explanation video without actually doing anything. Yeah, maybe summarise it if there is something.

Progress log 18:

organised wires, loaded my ram because havent done nothing in a while because IDF. at the end of ssesh new bug I will fix tommorow.

Progress log 19:

Loaded my ram which took a while again because I  event had time to work on this because of some things.  fixed the bug from the previous session (turns out the reset pin of the interface chip wasent connected to the rest button correctly ).

Tomorrow:

finish organization

watch part 3 vid

Progress log 20:

I downloaded and  assembler called "vasm".  and I wrote assembly code to do what I did before I add the assembler.  I also commented on the code carefully to understand what it does . also, I watched the entire part 3 video.tomorrow I'm excited to start actually connecting the thing to a screen.

Progress log 21:

Started part 4! connected and turned on the LED screen. and the contrast setting is working.

Progress log 22:

Finally finished part 4! Hello world on the screen is working! I  started the session by connecting the LCD interface pins into the port B of the interface chip and part of port A. then I watched the video and understood the basic premise and the code. then I  copied the vasm code, uploaded it to the EEPROM using the programmer, plugged the EEPROM back again, and the Hello world Program worked.

In the next Session I need to:

Refresh My understanding of the code and the system. in general ( and update the summary with untouched parts) ( make sure you revisit the address range concept, low level ).

Organise the lcd to interface data lines cabels ben eater style.

you will forget all the extra documents that were not currently saved in the PC, like the led linking stuff and the first macrom. Just don't make everything organised! Just save them somehow so you will remember in the future when you make everything look nice

Progress log 23:

I Replaced the original messy wires to ben eater style ones between port b and the lcd screen.  I had a bug which in the screen didn't work. It was stupid! I realised the mistake was that I forgot to connect parts of port A into the LCD screen (WHY DO I NEED PORT A???)  and then I read all the computer architecture and notes and started to load my RAM with everything again. I feel like I don't have a good understanding as I used to

Progress log 24 (1 hour):

I was kind of not ready to move to the next video because I feel like I don't fully understand the system. I think this is due to the code itself and to the interface chip, so I started reading the code again, which is now clearer. I also have GitHub with everything at once

Progress log 25 (1 hour):

spent the first 40 minutes loading up my ram because something about the system didn't seem clear to me. I realised it was the interface chip and the LCD and the extra LCD pins that are connected through the interface chip, last three port A pins  so I wrote a summary for the interface chip, understood how it works better. I also did that for the LCD. I talked and asked questions about both of them and summarised with GPT. Also, I progressed through the Part 5 video in 8 minutes.

Progress log 26:

Watched the entire part 5 video about the stack. then I wrote a summery about the stack.  after I wrote the initial summary, I gave it to JGPT asked it to refine it.  it did a pretty cool good job, and I just copied the summary, but I think this offloads a lot of the understanding from now on. I want to write the summary completely on my own with good wording and language, and then I can ask GPT for refinement without copying and pasting. Just add refinements on my own or change the text on my own. I think just asking him to refine the summary, copying it, and controlling the new, better summary is not going to do it for me to understand stuff well.

Progress log 27:

started connecting the RAM chip and made 14 ben eater style wires. which took a while.

Progress log 28 (45 minutes):

Connected the RAM to the rest of the board except its chip select and output enable pins.

Progress log 29:

After the new RAM instalment and the new LO world code, the programme didn't work. so I started debugging. First of all, I rechecked a lot of the connections, and then I got the EEPROM out. I put the old LO world programme without the subroutines, removed the RAM, and checked if everything works. It does work, which means the RAM connection is the problem. Now I'm going to recheck if the logic works, if the logic of the tree RAM activates the pin, or the address/databus (in the next session).

Progress log 30 (1 hour):

More debugging ahhhhh. Seems to be the data Buss.

Progress log 30:

more debugging. The problem seems to be the address bus connection. While debugging, I made a new problem with the connection between the VI interface chip and the LCD. I need to fix it tomorrow to organise everything before I can actually touch the address from the EEPROM to the RAM. The address bus connection, and only then can I fix it. The system should work, and I should finish with this disgusting thing