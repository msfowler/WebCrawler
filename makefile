EXE=bin/crawler
TEST=bin/test
LIBSRC=utils/src
LIB=lib/lib.a
LIB_OBJ=utils/obj/StringUtil.o utils/obj/URLInputStream.o utils/obj/FileInputStream.o \
        utils/obj/HTTPInputStream.o utils/obj/CommandRunner.o utils/obj/FileSystem.o \
        utils/obj/HTMLToken.o utils/obj/HTMLTokenizer.o
OBJ_FILES= obj/WebCrawler.o obj/URL.o obj/StopWords.o obj/Page.o obj/Occurrence.o  obj/OcrBST.o \
		  obj/OccurrenceSet.o obj/WordParser.o obj/HTMLValidator.o obj/PageDownloader.o \
		  obj/main.o obj/PageQueue.o obj/PageLinkedList.o obj/KeywordPair.o obj/PageBST.o \
		  obj/PageHistory.o obj/KeywordPairBST.o obj/KeywordIndex.o obj/HTMLParser.o obj/XMLPrinter.o 

TEST_OBJ= obj/URL.o obj/StopWords.o obj/Page.o obj/Occurrence.o  obj/OcrBST.o \
		  obj/OccurrenceSet.o obj/WordParser.o obj/HTMLValidator.o obj/PageDownloader.o \
		  obj/test.o obj/PageQueue.o obj/PageLinkedList.o obj/KeywordPair.o obj/PageBST.o \
		  obj/PageHistory.o obj/KeywordPairBST.o obj/KeywordIndex.o obj/HTMLParser.o obj/XMLPrinter.o obj/WebCrawler.o
		 


bin : $(EXE)

$(EXE) : $(OBJ_FILES) $(LIB)
	g++ -g -Wall -o $(EXE) $(OBJ_FILES) $(LIB)

test : dotest

dotest : $(TEST)
	$(TEST)
	
$(TEST) : $(TEST_OBJ) $(LIB)
	g++ -g -Wall -o $(TEST) $(TEST_OBJ) $(LIB)
	
lib : lib/lib.a

lib/lib.a : $(LIB_OBJ)
	ar r lib/lib.a $(LIB_OBJ)

clean :
	rm -f  obj/*
	rm -f bin/*
	rm -f lib/*
	rm -f utils/obj/*

obj/main.o : src/main.cpp
	g++ -g -Wall -c -o obj/main.o -I inc -I utils/inc src/main.cpp

obj/test.o : src/test.cpp inc/URL.h inc/Page.h
	g++ -g -Wall -c -o obj/test.o -I inc -I utils/inc src/test.cpp 

obj/Page.o : src/Page.cpp inc/URL.h inc/URL.h
	g++ -g -Wall -c -o obj/Page.o -I inc -I utils/inc src/Page.cpp
	
obj/StopWords.o : src/StopWords.cpp inc/StopWords.h utils/inc/FileSystem.h
	g++ -g -Wall -c -o obj/StopWords.o -I inc -I utils/inc src/StopWords.cpp

obj/URL.o : src/URL.cpp inc/URL.h
	g++ -g -Wall -c -o obj/URL.o -I inc -I utils/inc src/URL.cpp

obj/Occurrence.o : src/Occurrence.cpp inc/Occurrence.h
	g++ -g -Wall -c -o obj/Occurrence.o -I inc -I utils/inc src/Occurrence.cpp

obj/OcrBST.o : src/OcrBST.cpp inc/OcrBST.h
	g++ -g -Wall -c -o obj/OcrBST.o -I inc -I utils/inc src/OcrBST.cpp

obj/OccurrenceSet.o : src/OccurrenceSet.cpp inc/OccurrenceSet.h
	g++ -g -Wall -c -o obj/OccurrenceSet.o -I inc -I utils/inc src/OccurrenceSet.cpp

obj/WordParser.o : src/WordParser.cpp inc/WordParser.h
	g++ -g -Wall -c -o obj/WordParser.o -I inc -I utils/inc src/WordParser.cpp

obj/HTMLValidator.o : src/HTMLValidator.cpp inc/HTMLValidator.h
	g++ -g -Wall -c -o obj/HTMLValidator.o -I inc -I utils/inc src/HTMLValidator.cpp

obj/PageDownloader.o : src/PageDownloader.cpp inc/PageDownloader.h
	g++ -g -Wall -c -o obj/PageDownloader.o -I inc -I utils/inc src/PageDownloader.cpp 

obj/PageLinkedList.o : src/PageLinkedList.cpp inc/PageLinkedList.h
	g++ -g -Wall -c -o obj/PageLinkedList.o -I inc -I utils/inc src/PageLinkedList.cpp

obj/PageQueue.o : src/PageQueue.cpp inc/PageQueue.h
	g++ -g -Wall -c -o obj/PageQueue.o -I inc -I utils/inc src/PageQueue.cpp

obj/KeywordPair.o : src/KeywordPair.cpp inc/KeywordPair.h
	g++ -g -Wall -c -o obj/KeywordPair.o -I inc -I utils/inc src/KeywordPair.cpp

obj/PageBST.o : src/PageBST.cpp inc/PageBST.h
	g++ -g -Wall -c -o obj/PageBST.o -I inc -I utils/inc src/PageBST.cpp

obj/PageHistory.o : src/PageHistory.cpp inc/PageHistory.h
	g++ -g -Wall -c -o obj/PageHistory.o -I inc -I utils/inc src/PageHistory.cpp

obj/KeywordPairBST.o : src/KeywordPairBST.cpp inc/KeywordPairBST.h
	g++ -g -Wall -c -o obj/KeywordPairBST.o -I inc -I utils/inc src/KeywordPairBST.cpp

obj/KeywordIndex.o : src/KeywordIndex.cpp inc/KeywordIndex.h
	g++ -g -Wall -c -o obj/KeywordIndex.o -I inc -I utils/inc src/KeywordIndex.cpp

obj/HTMLParser.o : src/HTMLParser.cpp inc/HTMLParser.h
	g++ -g -Wall -c -o obj/HTMLParser.o -I inc -I utils/inc src/HTMLParser.cpp

obj/WebCrawler.o : src/WebCrawler.cpp inc/WebCrawler.h
	g++ -g -Wall -c -o obj/WebCrawler.o -I inc -I utils/inc src/WebCrawler.cpp

obj/XMLPrinter.o : src/XMLPrinter.cpp inc/XMLPrinter.h
	g++ -g -Wall -c -o obj/XMLPrinter.o -I inc -I utils/inc src/XMLPrinter.cpp

utils/obj/StringUtil.o : utils/src/StringUtil.cpp utils/inc/StringUtil.h
	g++ -g -Wall -c -o utils/obj/StringUtil.o -I utils/inc utils/src/StringUtil.cpp

utils/obj/URLInputStream.o : utils/src/URLInputStream.cpp utils/inc/StringUtil.h \
  utils/inc/CS240Exception.h utils/inc/HTTPInputStream.h utils/inc/FileInputStream.h \
  utils/inc/URLInputStream.h utils/inc/InputStream.h
	g++ -g -Wall -c -o utils/obj/URLInputStream.o -I utils/inc utils/src/URLInputStream.cpp

utils/obj/FileInputStream.o : utils/src/FileInputStream.cpp utils/inc/FileInputStream.h \
  utils/inc/CS240Exception.h
	g++ -g -Wall -c -o utils/obj/FileInputStream.o -I utils/inc utils/src/FileInputStream.cpp

utils/obj/HTTPInputStream.o : utils/src/HTTPInputStream.cpp utils/inc/HTTPInputStream.h \
  utils/inc/StringUtil.h utils/inc/CS240Exception.h
	g++ -g -Wall -c -o utils/obj/HTTPInputStream.o -I utils/inc utils/src/HTTPInputStream.cpp

utils/obj/CommandRunner.o : utils/src/CommandRunner.cpp utils/inc/CS240Exception.h \
  utils/inc/StringUtil.h utils/inc/CommandRunner.h
	g++ -g -Wall -c -o utils/obj/CommandRunner.o -I utils/inc utils/src/CommandRunner.cpp

utils/obj/FileSystem.o : utils/src/FileSystem.cpp utils/inc/FileSystem.h utils/inc/CS240Exception.h \
  utils/inc/UnitTest.h
	g++ -g -Wall -c -o utils/obj/FileSystem.o -I utils/inc utils/src/FileSystem.cpp

utils/obj/HTMLToken.o : utils/src/HTMLToken.cpp utils/inc/HTMLToken.h
	g++ -g -Wall -c -o utils/obj/HTMLToken.o -I utils/inc utils/src/HTMLToken.cpp

utils/obj/HTMLTokenizer.o : utils/src/HTMLTokenizer.cpp utils/inc/HTMLTokenizer.h 
	g++ -g -Wall -c -o utils/obj/HTMLTokenizer.o -I utils/inc utils/src/HTMLTokenizer.cpp
	
	



	


