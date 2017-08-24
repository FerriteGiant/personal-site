+++
date = "2016-09-24T20:44:37-05:00"
title = "Lists of Top 100 Books" 
showonlyimage = false
image = "projects/booklists/Books.svg"
draft = false

+++

Find the most recommended books and authors by merging lists of top 100 books.
<!--more-->

I love reading and I've often thought of working my way through reading every book on a "top books" list. But which list to choose? What books show up consistently? What authors are always represented but with different works? How representative are book lists with regards to historical works? 

I was thinking about these questions at the same time as I was interested in learning more about bash programming and AWK. This project is the result.

#### Which Book Lists to Choose?

I decided to stick to top 100 lists and to avoid specific lists like "Top 100 scifi novels." Some of the following are chosen by voting readers and some by literary experts. 

* [BBC's Big Read Top 100](http://www.bbc.co.uk/arts/bigread/top100.shtml)
* [The 100 Favorite Novels of Librarians](http://thegreatestbooks.org/lists/107)
* [Goodreads Top 100 Literary Novels of All Time](http://www.goodreads.com/list/show/13086.Goodreads_Top_100_Literary_Novels_of_All_Time)
* [Harvard Book Store Top 100 Books](http://www.harvard.com/shelves/top100/)
* [Modern Library 100 Best Novels (Board's list and Reader's list)](http://www.modernlibrary.com/top-100/100-best-novels/)
* [NPR 100 Best Beach Books](http://www.npr.org/templates/story/story.php?storyId=106983620)

#### Data Wrangling

I downloaded the raw HTML for each page and wrote AWK scripts to pull out the title and author.


An example of the HTML, in this case from GoodReads.
``` html
  <tr itemscope itemtype="http://schema.org/Book">
      <td valign="top" class="number">1</td>
    <td width="5%" valign="top">
      <a name="1885"></a>
      <a href="/book/show/1885.Pride_and_Prejudice" title="Pride and Prejudice">
          <img alt="Pride and Prejudice" class="bookSmallImg" src="http://d202m5krfqbpi5.cloudfront.net/books/1320399351s/1885.jpg" />
</a>    </td>
    <td width="100%" valign="top">
      <a href="/book/show/1885.Pride_and_Prejudice" class="bookTitle" itemprop="url">
        <span itemprop='name'>Pride and Prejudice</span>
</a>      <br/>
        <span class='by smallText'>by</span>
<span itemprop='author' itemscope='' itemtype='http://schema.org/Person'>
<a href="http://www.goodreads.com/author/show/1265.Jane_Austen" class="authorName" itemprop="url"><span itemprop="name">Jane Austen</span></a>
</span>
```
The following AWK script was used to pull out the title and author and write that information to a tab delimited file. 

``` awk
#!/usr/bin/awk
#awk -f extract<name>.awk -f functionLibrary.awk <name>.html
#Source: http://www.goodreads.com/list/show/13086.Goodreads_Top_100_Literary_Novels
BEGIN{
FS="<[^>]+>";
OFS="\t";
lineCount=100;
rankIterator=0;
}

FNR==1{
split(FILENAME,fileNameArray,".");
outputFile = fileNameArray[1]".table"; 
}

/itemprop='name'/{
title=$2
#print FNR,title
}

/class="authorName"/{
author=$3
#print FNR,author
currentLine=FNR
}
FNR==currentLine{
numNames=split(author,authorNameArray," ");
firstNames=join(authorNameArray,1,numNames-1);
#rank=weightBook(lineCount,rankIterator++);
print title,authorNameArray[numNames],firstNames > outputFile;
}
```


The result was a file for each list with the book title and the authors name on each line (family name followed by given name).

```
Pride and Prejudice Austen  Jane
1984  Orwell  George
The Great Gatsby  Fitzgerald  F. Scott
Jane Eyre Brontë  Charlotte
Crime and Punishment  Dostoyevsky Fyodor
Lolita  Nabokov Vladimir
The Adventures of Huckleberry Finn  Twain Mark
Of Mice and Men Steinbeck John
Wuthering Heights Brontë  Emily
Brave New World Huxley  Aldous
```

To merge the lists I used another AWK script, this time called from a bash script. This script also counted up the number of times the book shows up in a list and which lists it showed up in.

``` bash
#!/bin/bash
#usage: ./tabulateBooks.sh

awk -f tabulateBooks.awk \
../rawData/bookman_librarians.table \
../rawData/bbc_the_big_read.table \
../rawData/modern_library_readers.table \
../rawData/modern_library_board.table \
../rawData/npr_beach_books.table \
../rawData/good_reads.table \
../rawData/harvard_bookstore.table \
| sort -t"," -k1.2,1gr -k2.2,2gr > tabulatedBooks.csv
```

``` awk
BEGIN{
  FS="\t"; #Input delimiter
  OFS=","; #Output delimiter
  lineCount=100 #Number of items in the longest list
}

{ #for every line in each file
title=toupper($1)
authorLast=$2
authorFirst=$3
rank=lineCount-(FNR-1)
#bookArray[title]+=rank
NumOfListsArray[title]+=1
FirstNameArray[title]=authorFirst
LastNameArray[title]=authorLast
#Pull out filename sans extension 
len = split(FILENAME,N1,"/")
split(N1[len],N2,".")
listName = N2[1]
#Append which lists the book appears in and the rank it has in that list
FileNameArray[title]=(FileNameArray[title] "\",\"" listName "\",\"" rank)
totalRankArray[title]=(totalRankArray[title] + rank)
}



END{
#print "-------------------"
  for(title in FirstNameArray) {
      gsub(/^\",\"/,"",FileNameArray[title]) #Remove extra delimter 
        # Number of lists book is in,total rank, book title, author first name, last name, lists in which book appears and rank in that list
          print "\""NumOfListsArray[title]"\"","\""totalRankArray[title]"\"","\""title"\"","\""FirstNameArray[title]"\"","\""LastNameArray[title]"\"","\""FileNameArray[title]"\""
            }
}
```

Of course some duplicates slipped through since some lists had typos, title variations, etc... Here I gave in and used python to search through the merged list for likely duplicates by calculating the [Jaccard Index](https://en.wikipedia.org/wiki/Jaccard_index) for every combination of books in the list. Once I found the duplicates I corrected the errant names in the relevant source files and recreated the merged list.

``` python
#!/usr/bin/python

import sys

#####################################

def jaccard_index(set_1,set_2):
        n = len(set_1.intersection(set_2))
        return n / float(len(set_1) + len(set_2) - n)

#####################################

fileName=str(sys.argv[1])

shingleLen=4

with open(fileName,'r') as f:

  data = f.readlines()

  lineNumA=0
  for line in data:
    line=line.rstrip('\n')
    primaryShingle=[line[i:i + shingleLen] for i in range(len(line) - shingleLen + 1)]
    primarySet=set(primaryShingle)

    lineNumB=0
    for ll in data:
      if lineNumA < lineNumB:
        ll=ll.rstrip('\n')
        secondaryShingle=[ll[k:k + shingleLen] for k in range(len(ll) - shingleLen + 1)]
        secondarySet=set(secondaryShingle)

        jac = jaccard_index(primarySet,secondarySet)
        if jac > .35:
          print "%.3f\n%s\n%s"%(jac,line,ll)
          print "-----------"
      #print lineNumB
      lineNumB += 1
    #print lineNumA
    lineNumA += 1
```

This left me with a list of 443 unique books. The next step was to determine the year each book was published. Using curl I ran the title and author as search terms through Google and WolframAlpha and was able to pull out the publishing date for nearly every book. The last few I filled in by hand.

This script looks to see if the date is already known (since I ran this quite a few times) and if it isn't, tries to determine the date using Google and then WolframAlpha.

``` bash
#!/bin/bash
#Usage: ./tabulateBooks.sh tabulatedBooks.csv
: > tempdatesfile #Create empty file
cat $1 |  
while read line; do #for each line in the file do the following
  #The FPAT variable keeps commas inside quotes from being field seperators
  TA=$(echo "$line" | awk -vFPAT='([^,]*)|("[^"]+")' -vOFS=+ \
    '{print $3,$5}') #Title and author's last name
  Stitle=$(echo "$TA" | cut -d"+" -f1) #cut out just the title
  #Now remake $title and $TA with the '+' delimiter replacing spaces
  TA=$(echo $TA | awk -F'[ ]' 'BEGIN{OFS="+";} {$1=$1;print;}')
  title=$(echo $Stitle | awk -F'[ ]' 'BEGIN{OFS="+";} {$1=$1;print;}')


  sanitizedTitle=$( echo ${Stitle//\(/\\\(} ) #Replaces ( with \(
  sanitizedTitle=$( echo ${sanitizedTitle//\)/\\)} ) #Replaces ) with \)

  #Look for known dates in file (use perl regex because it works)
  year=$(cat tabulatedBooks_withDates.csv | grep -iP \
    "$sanitizedTitle\,\"([0-9]|\-[0-9])" \
    | awk -vFPAT='([^,]*)|("[^"]+")' '{gsub("\"","",$4); print $4}' )

  #Check if year is in the range 1000 to 2999 CE
  if (echo $year | grep -Eq '^[1-2][0-9][0-9][0-9]$')
  then
    printf 'Known year:%s\n' "$year"
    printf '\"%s\",%s\n' "$year" "$line" >> tempdatesfile
    continue
  fi

  #Check if year is in the range 0 to 999 CE
  if (echo $year | grep -Eq '^[0-9][0-9][0-9]$')
  then
    printf 'Known year:%s\n' "$year"
    printf '\"%s\",%s\n' "$year" "$line" >> tempdatesfile
    continue
  fi

  #Check if year is between 0 and 999 BCE
  if (echo $year | grep -Eq '^\-[0-9][0-9][0-9]$')
  then
    printf 'Known year:%s\n' "$year"
    printf '\"%s\",%s\n' "$year" "$line" >> tempdatesfile
    continue 
  fi

  if !(echo $year | grep -Eq '^[0-9][0-9][0-9][0-9]$')
  then
    echo "Searching for year"
    searchString=$(printf '%s%s' "$TA" "+published")
    year=$(curl --silent --user-agent "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36" \
    https://www.google.com/search?q=$searchString | \
    awk -f scrapeGoogle.awk)
  fi
  
  if !(echo $year | grep -Eq '^[0-9][0-9][0-9][0-9]$')
  then
    echo "Scraping google failed, trying wolframalpha..."
    searchString=$(printf '%s%s' "\"$title\"" "+first+publication+date")
    year=$(curl --silent --user-agent "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36" \
    http://www.wolframalpha.com/input/?i=$searchString | \
    awk -f scrapeWolfram.awk)
  fi

  if !(echo $year | grep -Eq '^[0-9][0-9][0-9][0-9]$')
  then
    #make sure $year is empty if it isn't a 4 digit number  
    year=""
    echo "FAILED: $Stitle"
  fi

  printf '\"%s\",%s\n' "$year" "$line" >> tempdatesfile
  
done
: > tempdatesfile2
awk -vOFS="," -vFPAT='([^,]*)|("[^"]+")' \
  '{t=$1; $1=$2; $2=$3; $3=$4; $4=t; gsub(",,",","); \
  print >> "tempdatesfile2"}' tempdatesfile
rm tempdatesfile
mv tabulatedBooks_withDates.csv tabulatedBooks_withDates.csv.backup 
mv tempdatesfile2 tabulatedBooks_withDates.csv
```

These are the helper AWK scripts to interpret the downloaded HTML.

``` awk
#For google results
#!/usr/bin/awk
BEGIN{
RS="<[^>]+>"; #Make each HTML tag a row divider
OFS="+";
ORS="";
}

/Originally published/{
if ($0=="Originally published") #Did it work?
  pubNR=NR #Remember row number
else
  next #No luck, proceed to next book
}


NR==pubNR+3{ #Date will be 3 rows after the 'originally published' text
dateArrayLength=split($0,dateArray," ")
year=dateArray[dateArrayLength] #Pull out just the year
print year
}

```

``` awk
#For wolframalpha results
#!/usr/bin/awk
BEGIN{
FS="\"";
OFS="";
}

/stringified/{
c++;
if(c==2){
  dateArrayLength=split($4,date," ")
  year=date[dateArrayLength]
  print year
  }
}
```

At this point I have a delimited file containing the book title, author name, publishing date, number of lists the book appears in, and which lists those are and the rank in each list..


#### Graphs 'n Things



