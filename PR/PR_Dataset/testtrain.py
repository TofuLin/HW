def separatefile(infile,outfile,outfile1):
 
 infopen = open(infile,'r')
 outopen = open(outfile,'w')
 outopen1 = open(outfile1, 'w')
 lines = infopen.read()
 i = 0
 for line in lines:
     i +=1
 if i % 2 == 0:
    outopen.write(line)
 else:
    outopen1.write(line)
 infopen.close()
 outopen.close()
separatefile("wine.data","test.data","train.data")
