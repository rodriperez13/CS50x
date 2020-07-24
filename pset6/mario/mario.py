height = int(input("Height: "))
print(type(height))
while height > 8 or height <= 0:
    height = int(input("Height: "))
if height == 1:
    print("#  #")
elif height == 2:
    print(" #  #")
    print("##  ##")
elif height == 3:
    print("  #  #")
    print(" ##  ##")
    print("###  ###")
elif height == 4:
    print("   #  #")
    print("  ##  ##")
    print(" ###  ###")
    print("####  ####")
elif height == 5:
    print("    #  #")
    print("   ##  ##")
    print("  ###  ###")
    print(" ####  ####")
    print("#####  #####")
elif height == 6:
    print("     #  #")
    print("    ##  ##")
    print("   ###  ###")
    print("  ####  ####")
    print(" #####  #####")
    print("######  ######")
elif height == 7:
    print("      #  #")
    print("     ##  ##")
    print("    ###  ###")
    print("   ####  ####")
    print("  #####  #####")
    print(" ######  ######")
    print("#######  #######")
elif height == 8:
    print("       #  #")
    print("      ##  ##")
    print("     ###  ###")
    print("    ####  ####")
    print("   #####  #####")
    print("  ######  ######")
    print(" #######  #######")
    print("########  ########")

