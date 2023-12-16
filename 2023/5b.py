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

def get_val(n):
    for phase in range(len(parse_order)):
        n = get_result(n, data[phase])
    return n

def find_min(x, y, local_min=None, iter=0):
    #print(f"Finding between {x} and {y}")
    mid = int((x+y)/2)
    val_bot = get_val(x)
    val_mid = get_val(mid)
    val_top = get_val(y)

    #print("Values: ", val_bot, val_mid, val_top)
    iter = iter+1
    if local_min == None:
        local_min = min([val_bot, val_mid, val_top])

    if (x-y)**2 == 1:
        local_min = min([val_bot, val_mid, val_top])
        #print("Final", local_min)
        return local_min

    if local_min in range(min(val_bot, val_mid), max(val_bot, val_mid)):
        local_min = find_min(x, mid, local_min, iter)
    elif local_min in range(min(val_top, val_mid), max(val_top, val_mid)):
        local_min = find_min(mid, y, local_min, iter)

    return local_min
    

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
    min_l = 1561691833
    for x in it:
        span = next(it)
        n = find_min(x, x+span)
        if n < min_l:
            min_l = n
            #print(min_l)
    print(min_l)

    exit(0)

