formNode=[]
for read in open('com-youtube.ungraph.txt'):
	formNode.extend(read.strip().split())

formNode=map(int,formNode)
lst=list(formNode)

file=open('com-youtube.ungraph.txt','r')
totaldegree=len(lst)
node=1134890
averagedegree=totaldegree/float(node)
outfile=open("averagedegree.txt","w")
outfile.write("%s"%averagedegree)
outfile.close()
print float(averagedegree)
print totaldegree