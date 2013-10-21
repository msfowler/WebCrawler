Web Crawler is a program that downloads webpages by following all the
links from a given base URL recursively and indexes the pages by
keyword. 

TO BUILD:
	- Check out all the files
	- Type "Make"

TO RUN:

	-The binary is in WEBCRAWLER/bin
	-USAGE: crawler <start-url> <output-file> <stopword-file>
	- <start-url> is the base URL. Be careful what you give it if you
	don't want to start downloading large amounts of websites. 
	- <output-file> is where you want to dump the output
	- <stopword-file> is a text file containing words to skip when
	  indexing such as "a", or "the" 

A description of the data structures is contained in docs. 

