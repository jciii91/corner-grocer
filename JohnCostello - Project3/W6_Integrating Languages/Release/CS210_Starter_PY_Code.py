# function to print all of the items and quantities in the input file
def PrintItems():
    # open the input file, add each line to a list
    itemList = []
    with open('Input.txt') as file:
        for line in file:
            itemList.append(line.strip())

    # count each unique item, track which items have been counted in itemTracker
    itemTracker = []
    for item in itemList:
        if (itemTracker.count(item) is not 0):
            continue
        else:
            print(item + ": " + str(itemList.count(item)))
            itemTracker.append(item)

# search the input file for the search term, return the item count if the item is found
# return 0 if the item is not found
def GetItemQuantity(searchTerm):
    itemList = []
    with open('Input.txt') as file:
        for line in file:
            itemList.append(line.strip())

    for item in itemList:
        if (item == searchTerm):
            return itemList.count(item)

    return 0

# create the .dat file to be used as the input for the histogram function in C++
def PrintHistograms():
    # open the input file and add its contents to a list
    itemList = []
    with open('Input.txt') as file:
        for line in file:
            itemList.append(line.strip())

    # if the file exists, clear it. otherwise, a new file is made
    f = open("frequency.dat", "w")
    f.close()
    # open the file in append mode
    f = open("frequency.dat", "a")

    # write a line to the file for each unique item found in the input
    # each line has the item name and its count
    itemTracker = []
    for item in itemList:
        if (itemTracker.count(item) is not 0):
            continue
        else:
            f.write(item + " " + str(itemList.count(item)) + "\n")
            itemTracker.append(item)

    f.close()