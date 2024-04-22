<h1>WoW Jewelcrafting Reagent to CSV</h1><br>
<body>This is a pretty basic file stream c++ program I made for my own convenience of tracking jewelcrafting production in modern WoW.<br><br>
It parses a WoW chatlog for gems produced during prospecting and combines and sorts the amounts of each gem produced into a csv file based on the ordering in allOrder.txt<br><br>
The item collecting function only looks for items that have a quality tier associated with them so in theory it could work for non-jewelcrafting items, but I haven't tested it - additionally 
these items would not be sorted by default as the allOrder.txt file only contains gems.<br><br>
See the example.csv file created from the ExampleWoWChatLog.txt file for an idea of what the ouput.csv file looks like. Open the .csv files in a spreadsheet program to view them properly.<br><br>
</body>
<h2>How do you obtain a chatlog?</h2>
<body>Type '/chatlog' into the chat box in WoW and then, after logging what you wanted and closing the game, <br> locate World of Warcraft\_retail_\Logs\WoWChatLog.txt<br><br>
This WoWChatLog.txt file continually builds on itself - it is not split up by seperate logging sessions. To get a specific time period look for the date on the left.<br><br>
Each line of the chatlog contains date and time as such: (month)/(day) (hour):(minute):(second).(millisecond)<br></body>
