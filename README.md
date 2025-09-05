# interesting-idea

I was going through some old programs I wrote, and one of the programs was for filling files with random characters. You were allowed to choose the size.
So I used that program to write 1.1 GBs of characters to a file. I shall include that program in this repository as well.

I used cat to display the contents of the file in my terminal, and it seemed to never end. My screen was filled with a constant stream of characters, Then, I thought of an interesting question. In this huge file of random characters, how many real words would I be able to find? Checking how a word was real wasn't my main problem. I have a wordlist of 100000+ words.

So, I started writing a program to go through the entire file, and look for words. 

I knew I would need to use hashing for checking if a word is real, because manually comparing each string to 100000+ words is a tedious task, and I wasn't writing the program for small files. The files I was going to use as input would have upwards of 1 GBs of characters. There are too many strings. The least I could do was make the checking a little faster.

Hashing isnt that simple, with this many possible strings, you have to prevent hash collisions too.

So, first I tried to use a 2D array, where one of the coordinates would be decided by hash function H1, and the second one by hash function H2. H1 and H2 were entirely different hash algorithms. But my system crashed whenever I tried to run that, so I came up with another approach.

I used a good hash function first, and if a string's hash matched with the hash of a real word, I compared that string to every string in the list of the real words. 

It was a compromise. It was the best that I could come up with at that moment, because I was in too deep, It was too late to switched to some approach with linked lists.

Later, I also learned that fgetc() IS notoriously slow, and I should've used fread, because it can read a lot of bytes **quickly**. While coding the program, I was under the impression that an fread call would be slow. 
