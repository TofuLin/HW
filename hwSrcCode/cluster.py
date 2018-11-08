# -*- coding: utf-8 -*-
"""
Created on Tue Mar  6 19:53:15 2018

@author: chiming
"""
import csv
fn="com-youtube.ungraph.csv"
maxIDX=1157827
#fn="test.csv"
#maxIDX=6
degreeLst=[]
preIndex=-1
nowIndex=-1
counter=0

with open(fn,encoding="big5") as f:
    for i in range(4):
        row=f.readline()
        print(row)
    adjNodes=[]
    idxSet=set()
    for row in csv.reader(f):
        counter+=1
        nowIndex=eval(row[0])-1
        if preIndex < nowIndex:
            for i in range(nowIndex-preIndex-1):
                adjNodes=[]
                if len(degreeLst) in idxSet:
                    adjNodes.append(-1)     #代表是節點,但無鄰節點
                    idxSet.remove(len(degreeLst))
                else:
                    adjNodes.append(-2)   #代表不是節點
                degreeLst.append(adjNodes)
            adjNodes=[]
            idxSet.add(eval(row[1])-1)
            adjNodes.append(eval(row[1])-1)
            if len(degreeLst) in idxSet:
                idxSet.remove(len(degreeLst))
            degreeLst.append(adjNodes)
            preIndex=nowIndex
        else:
            idxSet.add(eval(row[1])-1)
            adjNodes.append(eval(row[1])-1)            
        if counter%10000==0:
            print("counter1=",counter)
#print(degreeLst)
remainderIdx=maxIDX-len(degreeLst)
if remainderIdx> 0: # 補餘節點
    for i in range(remainderIdx): 
        if len(degreeLst) in idxSet:
            idxSet.remove(len(degreeLst))
            degreeLst.append([-1])
        else:
            degreeLst.append([-2]) #代表不是節點
#print(degreeLst)
degree=0
triples=0
trangles=0
nodes=0
edges=0
counter=0
f=open('d:\\degreeList.csv','w+t',buffering=8192)
f.writelines("#node,degree,triples,triangles\n")
line=""
sumcc=0 #sum all clustering coefficient
for adjNodes in degreeLst:
    if len(adjNodes) > 200:
        print("node=",counter+1,",degree=",len(adjNodes),",waitting!")
    adjNodes.sort()
    trangles=0
    if adjNodes[0] >-2:        
        nodes+=1
        if adjNodes[0] > -1:
            degree=len(adjNodes)
            #計算triangles
            if len(adjNodes)>1:
                for i in range(len(adjNodes)):
                    for j in range(len(adjNodes)-i-1):
                        if adjNodes[i+1+j] in degreeLst[adjNodes[i]]:
                            trangles+=1
            triples=int(degree*(degree-1)/2)                
            line=str(counter+1)+","+str(degree)+","+str(triples)+","+str(trangles)+"\n"
            if trangles>0:
                sumcc+= trangles/triples
            #修正degree
            for idx in adjNodes:
                if degreeLst[idx][0]==-1:
                   degreeLst[idx].clear()
                if idx>counter:
                    degreeLst[idx].append(counter)
                    edges+=1
        
        f.writelines(line)
    counter+=1
    if counter%5000==0:
        print("counter2=",counter)
#print(degreeLst)
#print("idxSet=",idxSet)
print("nodes=",nodes)
print("edges=",edges)
print("clustering coefficient=",sumcc/nodes)
f.flush()
f.close()
                         
                    
                    