import utils
import sys

s = "seeds:"
s2s = "seed-to-soil map:"
s2f = "soil-to-fertilizer map:"
f2w = "fertilizer-to-water map:"
w2l = "water-to-light map:"
l2t = "light-to-temperature map:"
t2h = "temperature-to-humidity map:"
h2l = "humidity-to-location map:"

parse_order = [s2s, s2f, f2w, w2l, l2t, t2h, h2l]
data = {}
almanac = {}
def get_result(num, range_list):
    for line in range_list:
        start = line[1]
        end = line[1]+line[2]
        if num in range(start, end):
            next = line[0]+(num-line[1])
            return next
    
    return num            


if __name__ == '__main__':
    args = utils.parse_args()
    fn = args.file
    seeds = []
    seed_pairs = []
    phase = 0
    with open(fn) as fh:
        for line in fh:
            line = line.strip()
            
            if s in line:
                seed_pairs = [int(x) for x in (line.split(": ")[1]).split(" ")]
                continue

            for i, item in enumerate(parse_order):
                try:
                    if parse_order[i+1] in line:
                        phase = i+1
                        continue
                except IndexError:
                    pass
                if phase == i:
                    if not(item in line or line == ""):
                        range_list = [int(x) for x in line.split(" ")]
                        #print(phase, item, range_list)
                        if phase not in data:
                            data[phase] = []
                        data[phase].append(range_list)
    L = []
    it = iter(seed_pairs)
    min_l = 1000000000
    for x in it:
        for i in range(next(it)):
            n = x+i
            for phase in range(len(parse_order)):
                n = get_result(int(n), data[phase])
            
            if n < min_l:
                min_l = n

    print(min_l)

    exit(0)