import utils
import sys


def find_number(line, start_index):
    #print(line[start_index:], start_index)
    lp = 0
    rp = 0
    lp_found = False
    for i, char in enumerate(line[start_index:]):
        #print(i, char)
        if lp_found and not char.isalnum():
            rp = i+start_index
            break

        if lp_found == False and char.isalnum():
            lp_found = True
            lp = i+start_index

    if lp !=0 and rp==0:
        rp = len(line)
    
    return lp, rp, line[lp:rp]
        
def get_numbers_in_neightborhood(p, c, n, loc):
    mat = [p ,c, n]
    if p == None:
        mat = [c, n]
    elif n == None:
        mat = [p, c]

    print(mat)
    j=0
    nums = []
    for row in mat:
        start_index = 0
        while True:
            lp, rp, num = find_number(row, start_index)
            if (lp == rp):
                break
            start_index = rp
            j = j+1

            #   loc-1       loc     loc+1
            #   X           X       X
            #   X           loc       X
            #   X           X       X   

            if lp in range(loc-1, loc+2) or rp-1 in range(loc-1, loc+2):
                print(f"Num {num} within range {lp}, {rp} in {[x for x in range(loc-1, loc+2)]}")
                nums.append(int(num))

    return nums


if __name__ == '__main__':
    args = utils.parse_args()
    fn = args.file

    p = None
    n = None
    sum = 0
    with open(fn) as fh:
        lines = fh.readlines()
        for i, line in enumerate(lines):
            c = line.strip()
            try:
                n = lines[i+1].strip()
            except IndexError:
                n = None

            print(f">>>>>>>>>>>>> {i}")


            j=0
            start_index = 0
            # Scan each line for *:
            # Look in line above or below for numbers in neighbor hood using indexes
            # If exactly two in nieghborbooh, then multiply and add them to the list
            # print res. 

            for j, char in enumerate(c):
                if char == "*":
                    print(f"Gear found at {j} on line {i}")
                    nn = get_numbers_in_neightborhood(p,c,n,j)
                    if len(nn) == 2:
                        power = nn[0] * nn[1]
                        print(f"POWER {nn[0]} * {nn[1]} = {power}")
                        sum = sum + power

            p = c


    print(sum)
    exit(0)