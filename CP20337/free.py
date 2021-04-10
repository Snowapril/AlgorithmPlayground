import copy

def worklist(works, reqs, acp):
	if works <= 0:
		return 0
	for x in acp:
		if req[works-1][0] > x[1] or reqs[works-1][1] < x[0] :
			continue
		else:
			return worklist(works-1, reqs, copy.deepcopy(acp))
	left = worklist(works-1,reqs,copy.deepcopy(acp))
	acp.append(reqs[works-1])
	right = worklist(works-1, reqs, copy.deepcopy(acp))
	print(acp)
	return max(left, right + reqs[works-1][2] - 10)

N = int(input())

requests = []
for x in range(N):
	requests.append(list(map(int,input().split())))

print(worklist(len(requests), requests, []) + 10)