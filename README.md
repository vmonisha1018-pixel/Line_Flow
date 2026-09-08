\# LINEFLOW - Command Line Text Editor


\## Project Idea

LineFlow is a simple command-line text editor written in C.

It stores each line of the document using a doubly linked list.



\## Data Structure

Doubly Linked List



Each node contains:

\- Text of the line

\- Pointer to the previous node

\- Pointer to the next node



\## Implemented Features



1\. Insert Line

&#x20;  Adds a new line at a specified position.



2\. Delete Line

&#x20;  Deletes a line using its line number.



3\. Display Document

&#x20;  Displays all current lines with their line numbers.



\## Commands



i - Insert line

d - Delete line

p - Display document

q - Quit



\## How to Compile



gcc main.c -o lineflow



\## How to Run



.\\lineflow



\## Error Handling



The program handles invalid line numbers, empty documents and invalid commands.