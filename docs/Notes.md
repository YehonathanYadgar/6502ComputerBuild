Whats mega megahertz? whats Hertz?
Hertz (Hz) and megahertz (MHz) are units that measure frequency  how often a repeating event occurs per second. The difference between them is simply scale.
1 Hertz  = 1 Hertz per second
1 kilo hertz = 1,000 hertz a second
1 megaHertz = 1,000,000 Hz (10^6 Hz) Per seconds

Why dose a CPU needs a clock?
To make sure everything happens serially and doesn't gets tangled up. (To set a pace for the CPU) (This needs extra expension)

What are interrupts?
A program that happens immediately When triggered. For example When the Emergency  button is pressed in the elevator it stops everything else and activates the alarm right away, and then return to its previous task (it doesn't fully leave at the moment of the press. First, the CPU finishes its current instruction; then it keeps the staging, which is in the register. Then it goes and does the interrupt thing, and then it continues from where it was.)  
 
 Interrupt Real Life Analogy:
 You are coding, then suddenly the oven makes its finished noise. In order for the food not to burn, you go turn off the oven, take out the food, and then you go straight into coding. 

Adress Buss ():
The Address buss tells the Memory which cell (Memory part) it wants to read or write to. the 6502 address buss as 16 pins in it. So the max memory unit that can work with it is 65,536 cells or about 64 kilo bytes. The address buss tells which thing it wants to read using binary code by settings certain outputs high and low according to the wanted cell he wants to read or write to.

Data Buss:
After the CPU uses the address buss to specify Which cell he wants to read. The CPU reads the data buss pins ( instructions come through the database ). in the 6502 The data buss is 8 inputs / output pins so it only works with max 8 bit of memory at once.

analogy:
The address bus is the shelf location you give the librarian ("aisle 12, shelf 4"). The data bus is the _book_ they hand you (or that you hand back).

EEPROM:
The EEPROM chip gets an Address Through his address buss and outputs the data from the specified cell through is dataBuss ( The CPU'S data buss is connected to the EEPROM'S dataBuss and this is the same for the address bus. )

incompatible EEPROM and CPU ranges:
Since the cpu I am using has 16 bit address buss that can access in total 65k different cells. and the EEPROM total memory is only 15 bits (28k total cells), there is a need to detect when the cpu tries to fetch something  from the EEPROM that isn't in the EEPROM'S memory range and prevent that fetch (I am not sure why yet). for this you take the 16'th pin from of the cpus address buss and  connect it to the EEPROM CE pin (the EEPROM's CE pin is active low, and the EEPROM  only works if its active). this solves the problem because if the 16'th bit is active it means that the cpu is out of the EEPROM'S  memory range, but theres a new problem when the cpu boots its boot startup starts from a couple of addresses outside of the EEPROM'S range  to combat this, you put a NAND gate between the sixteenth CPU pin and the EEPROM's CE pin.  now, the upper range of the CPU address bus addresses is active, and the lower range is not  and both problems are solved.

TO SUMMERIZE FIRST AND SECOND ORDER BITS

Two typs of buttons electronics

Learn about binary and hex

Register

 how do instructions work? It just seems to me at the moment that when I write, for example, 0 A9, the next byte is loaded in the data register, but why? How does this work 

write a note about the 650222 interface chip and nand gate configuration and also the wasted adress range. 



 
