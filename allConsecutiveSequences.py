

def run(inputs):
    print(inputs)
    all_sets2 = [{v} for v in inputs] # list of sets
    while len(all_sets2) > 1:
        all_sets = all_sets2
        all_sets2 = []
        inds = set()
        for ind1 in range(len(all_sets)):
            if ind1 in inds: continue
            for ind2 in range(len(all_sets)):
                if ind2 in inds: continue
                s1 = all_sets[ind1]
                s2 = all_sets[ind2] 
                if max(s1)+1 in s2 or min(s1)-1 in s2:
                    tmp_set = s2.union(s1)
                    if len(tmp_set) > len(s2):
                        s2 = tmp_set
                        all_sets2.append(s2)
                        inds.add(ind1)
                        inds.add(ind2)
     
        for ind in range(len(all_sets)):
            if ind in inds or len(all_sets2) == 0: continue
            all_sets2.append(all_sets[ind])
                        
    print(list(all_sets))
    
            



inputs = [5,2,99,4,3,1,100,102,101,104,103,201,202,203, 300,-1]

run(inputs)
