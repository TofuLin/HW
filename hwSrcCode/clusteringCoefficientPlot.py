# -*- coding: utf-8 -*-
"""
Created on Wed Mar  7 21:58:18 2018

@author: chiming
"""

import matplotlib.pyplot as plt
import numpy as np
import csv
fn="degreeList.csv"
x=[]
y=[]
triples=0
triangles=0
degree=0
sumdegree=0
sumtriples=0
sumtriangles=0
nodes=0
cc=0.0
sumcc=0
avgcc=0
nodeID=0
maxNodeID=0
with open(fn,encoding='Big5') as f:
    for i in range(1):
        row=f.readline()
        print(row)
    for row in csv.reader(f):
        nodeID=int(row[0])
        degree=int(row[1])
        triples=int(row[2])
        triangles=int(row[3])
        if triangles==0:
            cc=0
        else:
            cc=triangles/triples
        sumcc+=cc
        sumdegree+=degree
        sumtriples+=triples
        sumtriangles=triangles
        nodes+=1
        x.append(nodeID)
        y.append(cc)
        maxNodeID=nodeID
avgcc=sumcc/nodes
print('sumdegree=',sumdegree,'sumtriples=',sumtriples,'sumtriangles=',sumtriangles,'avgcc=',avgcc)

plt.figure(num=4,figsize=(8,4))
plt.scatter(x,y,s=1,c='b',alpha=1)
plt.xlim(1,maxNodeID)  #設置x軸座標範圍
plt.ylim(0,1)
plt.xlabel("nodeID")
plt.ylabel("clustering coefficient")
plt.hlines(avgcc,1,maxNodeID,color='red',linestyle='--')
plt.yticks(np.linspace(0,1,21))
plt.text(int(maxNodeID/2),avgcc+0.05,"avgVal="+str(avgcc)[0:4],fontdict={'size':16,'color':'r'})
plt.show()