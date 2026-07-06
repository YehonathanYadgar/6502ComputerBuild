Day 1 of electronics:
I watched the entire first vid of ben eater 6502 computer from 0. I connected the 6502 cpu to the mother bored, and saw the outputs of the address buss with an Arduino. (I haven't fully built the clock and connected it to the cpu, so currently I just use a button for this with single ticks.) Also I learned about interrupts, data buss and the basic looping function of the cpu (I think). 

Day 2:
I Opened up the EEPROM chip, and connected it into an NAND gate in order to make it work with the cpu Only in the range that fits with the EEPROM (15 bits). Also I learned about the basics Of how EEPROM works, and also tested if the NAND gates chip works. 

 day 3:
Organized most of the cables only 3 left to organize. 

Day 4:
I organized the final 3 remaining cables (Ben Eater style) which was relativity hard and took a decent amount of time. Then I tested the Arduino and found a bug the CPU was outputting stright 0's in the address buss I fixed this bug by fixing the reset buttons wiring. Currently I am trying to fix a new bug and understand why after a restart the cpu dosen't start like it should.

Day 5:
Fixed reset program not working properly bug. A few things fixed it:
First of all, some CPU pins didn't get enough power because they were connected through the 3.3 V power store of the Arduino. I figured this out by making a debug file, which is simple. It only checks and reads the analogue value of a certain pin of the Arduino, so I connected the cable and debugged this way. 

Also, using GPT, I realised part of the reason that the logs of the recent programme counter didn't seem correct is because of button bouncing. I fixed the button bouncing by making the button digital. 

Overall, I am happy with the consistency so far. But things are moving slowly. Tomorrow I want to put in like four hours because its weekend. I want to start by organising the cables a bit,  because stuff got a little bit messy. Also i want to connect the EEPROM to the CPU and completely finish part 2 of the series. 

Day 6:
Connected the address buss, and the dataBuss of the EEPROM and CPU together (This took a lot of time because all of the wires). 

Day 7:
Upload the basic EA program to the EEPROM, and it worked (I verified by reading the data buss pins of the cpu). It took me like an hour to upload the programme because of me being dumb and not understanding the correct position for the CPU. I continually asked AI what the problem is because I thought it wasn't the software and also didn't read carefully what the xg pro software outputted. It just explained exactly what I need to do. This really makes me think I need to be careful, and I already thought about it, using AI tools for learning in general. I think it's good, especially in learning, to only ask good questions. When I said good questions, I'm talking about the article, the hacker-style article about the good question stuff. This is the only question you should ask while learning and also probably in general right now with current AI. In order to not get atrophied, because this was just brain atrophy. Now I changed the EA programme a bit. The change was that in the reset sequence I changed the last two pins of the reset sequence values in the eeprom. For some reason I can't read it with the Arduino. I need to fix this! My plan is to:

1. First of all, get my RAM up to date to know everything works.
2. Check all of the connections and the code.
3. If it doesn't work, give all of the context to an AI and ask it a good question and try to figure it out this way.
4. 
overall, I am happy that I put in the two hours today, but the progress is really, really slow! I just currently logged the days when I am working. There were three that I didn't because of the army, and I finish at 9 each day from 7, so yeah, I need to move much faster 


Day 8:
Debugged all day, at the end of the two hours realized it was the clock pin not connected probably. arduino burned probably continue later

Day 9:
There was a short and the Arduino didn't turn on. I tried to figure out why for some time and didn't realise why, so I disconnected and connected everything, and then the short stopped shorting, I guess.  it took the whole day because it takes time to connect everything and disconnect.

Day 10:
Switched to orgenized wires because it was messy as hell.

Day 11:
readings weren't correct. I got "aaa" instead of "ea" from the data bus of the CPU .  also, I accidentally wired the Ben Ethersail wires above the EEPROM, so I couldn't get it out, which is a problem because I need to repeatedly take it out and programme it with the EEPROM programmer  so, for the 100th time, I took out all of the wires again because the wires about the EEPROM were at the bottom, and I wired everything up again. with no wires above the eeprom. The I checked evreything (with the debug file) and evreything works except of the ce pin which i will fix tommorow. ( for the check, I just hard connected it to ground since I saw it's not low at the beginning for some reason) Also i started working on the github and github workflow today since i realized its importent. Also short cabels first always in the wiring!!!!


![[Pasted image 20260701142458.png]]explain about this

Day 12:
After checking some wires with the Arduino analogue rig because I don't have a multimeter.  I realised the problem was the non-grid wasn't working, even though it got 2 signals as input. It still outputted one  after further checking, I realised this was because one of his pins was bent and not connected to the breadboard. Specifically, the GND one  using a plier, I fixed the pin's angle. Here is the NAND gate, and now everything worked.

Day 13:
Progressed like 11 min through the video. Made some ben eater style wires in Order to have some extra short bread board wires. Learned about the 650222 interface chip and the nand gate configuration. 



