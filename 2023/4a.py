import utils
import sys


def get_sets(line):
    line = line.split(':')[1]
    nums = line.split('|')
    return nums[0].split(), nums[1].split()
        
def get_match(winners, numbers):
    score = 0
    return score


if __name__ == '__main__':
    args = utils.parse_args()
    fn = args.file
    res = 0
    with open(fn) as fh:
        for line in fh:
            line = line.strip()
            w, c = get_sets(line)

            #print(line, w, c)
            
            w = set(w)
            c = set(c)
            num_win = w.intersection(c)
            res = res + int(pow(2, len(num_win)-1))
    print(res)
    exit(0)