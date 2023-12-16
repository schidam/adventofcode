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
        

if __name__ == '__main__':
    args = utils.parse_args()
    fn = args.file

    p = None
    n = None
    nums = []
    with open(fn) as fh:
        lines = fh.readlines()
        for i, line in enumerate(lines):
            c = line.strip()
            try:
                n = lines[i+1].strip()
            except IndexError:
                n = None

            print(f">>>>>>>>>>>>> {i}")
            print(f"{p}\n{c}\n{n}")

            j=0
            start_index = 0
            while True:
                lp, rp, num = find_number(line, start_index)
                if (lp == rp):
                    break

                start_index = rp
                j = j+1

                print("res:", j, lp, rp, num, len(c))
                start_col_index = lp if lp == 0 else lp-1
                end_col_index = rp if rp == len(c) else rp+1
                #print(start_col_index, end_col_index)

                try:
                    pass
                    if p == None:
                        #first row special handling:
                        for x in list(c):
                            for y in range(start_col_index, end_col_index):
                                try:
                                    if( not (n[y].isalnum() or n[y] == ".")):
                                        #print("First row: Found symbol near number", n, y)
                                        raise RuntimeError
                                except IndexError:
                                    print("Error", row, x, y)
                                    exit(2)
                    else:
                        mat = [p, c, n]
                        if n == None:
                            mat = [p, c]
                
                        # for each row, iterate through each colum and check if a symbol exists. 
                        # If so, then add the number and exit the loop
                        for row in mat:
                            for x in list(row):
                                for y in range(start_col_index, end_col_index):
                                    try:
                                        if( not (row[y].isalnum() or row[y] == ".")):
                                            print(f"Found symbol {row[y]} near number {num}")
                                            raise RuntimeError
                                    except IndexError:
                                        print("Error", row, x, y)
                                        exit(2)
                        
                except RuntimeError:
                    #print(f"Added {num}")
                    nums.append(int(num))    

                if (rp == len(c)):
                    print("end of line reached")
                    break
            p = c


    print(nums, sum(nums))
    exit(0)