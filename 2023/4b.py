import utils
import sys


scores = []
num_cards = []

def compute_score(i, line):
    line = line.split(':')[1]
    nums = line.split('|')
            
    w = set(nums[0].split())
    c = set(nums[1].split())
    score = len(w.intersection(c))
    scores[i] = score
    num_cards[i] = num_cards[i] + 1

    print(f"Looking at line{i}, matches = {score}, num_cards = {num_cards[i]}")
    
    for j in range(score):
        index = i+j+1
        num_cards[index] = num_cards[index] + num_cards[i]
        print(f"Adding {num_cards[i]} to index {index}")

if __name__ == '__main__':
    args = utils.parse_args()
    fn = args.file
    res = 0
    with open(fn) as fh:
        lines = fh.readlines()
        scores = [0] * len(lines)
        num_cards = [0] * len(lines)
        for i, line in enumerate(lines):
            line = line.strip()
            compute_score(i, line)


    res = sum(num_cards)
    print(res)

    print(num_cards)
    exit(0)