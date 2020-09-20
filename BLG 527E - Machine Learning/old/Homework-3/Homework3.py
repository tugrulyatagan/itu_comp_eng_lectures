import math
import time
import numpy as np

def classes(col,cs,cN):
    cls = []
    s = len(col)    
    for i in range(s):
        if cs[i] == cN:
            cls.append(col[i])
            
    return cls

def classProb(cs):
    classP = [ 0 for i in range(10) ]
    s = len(cs)    
    for i in range(s):
        classP[cs[i]] = classP[cs[i]] + 1

    for i in range(10):
        classP[i] = classP[i]/s
    return classP

def meanCls(cls):

    means = []
    s = len(cls)
    sc = len(cls[0])
    for j in range(0,sc):
        sum2 = 0
        for i in range(0,s):
            sum2 = sum2 + cls[i][j]
        means.append(sum2/s)
    return means

def indCM(covR):
    sc = len(covR[0])
    nCr = []
    nc = []
    for i in range(sc):
        if covR[i][i] < 0.1:
                nc.append(i)
    return nc
def removeZeroVariances(covR):
    sc = len(covR[0])
    nCr = []
    nc = []
    
    for i in range(sc):
        if covR[i][i] < 0.1:
                nc.append(i)
    
    newCls = []
    for i in range(sc):
        if i not in nc:
            bf = []
            for j in range(sc):
                if j not in nc:
                    bf.append(covR[i][j])
            newCls.append(bf)
            
    return newCls
                    
def fullCovMatrix(cls,means):
    sc = len(cls[0])
    covR =  [ [ 0 for i in range(sc) ] for j in range(sc) ]
    s = len(cls)
   
    for j in range(0,sc):
        for k in range(0,sc):
            for i in range(0,s):
                covR[j][k] = covR[j][k] + (cls[i][j] - means[j])*(cls[i][k] - means[k])
            covR[j][k] = covR[j][k]/s

    return covR

def diagCovMatrix(cls,means):
    
    s = len(cls)
    sum1 = 0
    z = 0
    sc = len(cls[0])
    covR =  [ [ 0 for i in range(sc) ] for j in range(sc) ]
    for j in range(0,sc):
        for i in range(0,s):
            covR[j][j] = covR[j][j] + (cls[i][j] - means[j])*(cls[i][j] - means[j])
        covR[j][j] = covR[j][j]/s

    return covR

def correlation(covR):
    sc = len(covR[0])
    nCrr = []
    for i in range(sc):
        crr = []
        for j in range(sc):
            if math.sqrt(covR[i][i])*math.sqrt(covR[j][j]) != 0:
                crr.append(covR[i][j]/(math.sqrt(covR[i][i])*math.sqrt(covR[j][j])))
            else:
                crr.append(0)
        nCrr.append(crr)

    return nCrr

def discriminantFuncfullCov(indxL, detL, covMs,ms,cP, inst):
    newInst = remInst(indxL[0], inst)
    newInst = np.asarray(newInst)
    max1 =  math.log(cP[0])- (np.dot(np.dot(newInst - ms[0], covMs[0]), np.transpose(newInst - ms[0])))/2 - math.log(detL[0])
    cnt = 0

    
    for t in range(1,10):
        newInst = remInst(indxL[t], inst)
        newInst = np.asarray(newInst)         
        gx = math.log(cP[t])-(np.dot(np.dot(newInst - ms[t], covMs[t]), np.transpose(newInst - ms[t])))/2 - math.log(detL[t])/2
        if max1 < gx:
            max1 = gx
            cnt = t
    return cnt

def discriminantFuncShCov(ind, covMs,ms,cP, inst):
    max1 = -999999999
    cnt = -1
    p = 0
    
    s = len(covMs)    

    for t in range(10):
        newInst = remInst(ind, inst)
        p = 0
        for j in range(s):
            if covMs[j][j] != 0:
                p = p + (pow((newInst[j] - ms[t][j])/covMs[j][j],2))

        p = math.log(cP[t]) - p/2

        
        if max1 < p:
            max1 = p
            cnt = t
   
    return cnt

def commonCovM(covMs, cP):
    sc = len(covMs[0])
    cSum =  [ [ 0 for i in range(sc) ] for j in range(sc) ]
    
    for k in range(10):
        for i in range(sc):
            for j in range(sc):              
                if i == j:
                    cSum[i][j] = cSum[i][j] + (cP[k]*covMs[k][i][j])
    return cSum;



def remInst(indx, inst):
    newInst = []
    for j in range(64):
        if j not in indx:
            newInst.append(inst[j])
    return newInst

def remMS(indx, means):
    newm = []
    
    for j in range(64):
        if j not in indx:
            newm.append(means[j])
    return newm

        
def crossValidation(t, col,cs):
    testset = []
    dataset = []
    csts = []
    dsts = []
    s = len(col)
    for j in range(10):
        for i in range((j*s)//10, ((j+1)*s)//10):
            if t != j:
                dataset.append(col[i])
                csts.append(cs[i])
            else:
                testset.append(col[i])
                dsts.append(cs[i])
    fullCovAssumption(dataset, testset, dsts, csts)
    sharedCovAssumption(dataset, testset, dsts, csts)
   

def fullCovAssumption(col,test, ts,cs):
    covMs = []
    detL = []
    indxL = []
    ms = []
    cP = classProb(cs)
    
    for i in range(0,10):
        cls = classes(col,cs,i)
        means = meanCls(cls)
        means = np.asarray(means)
        ms.append(means)
        ncm = fullCovMatrix(cls,means)
        indxL.append(indCM(ncm))
        ncm = removeZeroVariances(ncm)
        detL.append(np.linalg.det(ncm))     
        ncm = np.matrix(ncm)       
        inv = np.matrix.getI(ncm)
        covMs.append(inv)

    for y in range(10):
        ms[y] = remMS(indxL[y], ms[y])
    
    s = len(test)  
    crrct = 0
    for i in range(s):
        csNum = discriminantFuncfullCov(indxL, detL, covMs,ms,cP, test[i])
        if csNum == ts[i]:
            crrct = crrct + 1
    print("Full covariance assumption results : ")
    print("Accuracy : " + str((100*crrct)/s))

def sharedCovAssumption(col,test, ts,cs):
    covMs = []
    ms = []
    cP = classProb(cs)
    
    for i in range(0,10):
        cls = classes(col,cs,i)
        means = meanCls(cls)
        means = np.asarray(means)
        ms.append(means)        
        ncm = diagCovMatrix(cls,means)
        covMs.append(ncm)        
        ncm = np.matrix(ncm)
        
    
    cmnCM = commonCovM(covMs, cP)
    ind = indCM(cmnCM) #indicating the constants indexes
    
    cmnCM = removeZeroVariances(cmnCM)#removing the constants
    for y in range(10):
        ms[y] = remMS(ind, ms[y])
    
    s = len(test)
    
    crrct = 0
    for i in range(s):
        csNum = discriminantFuncShCov(ind, cmnCM,ms,cP, test[i])        
        if csNum == ts[i]:
            crrct = crrct + 1
    print("Shared diagonal covariance assumption results : ")
    print("Accuracy : " + str((100*crrct)/s))

f = open('optdigits.tra', 'r')
#f = open('optdigits.tes.txt', 'r')
dataset = []
j = 0
cs = []
insts = []
ko = 0
for line in f:
    c = []
    k = line.split(',')
    cs.append(int(k[64]))
    for i in range(0,64):
        c.append(int(k[i]))
    dataset.append(c)
f.close()

print("Calculating Parameters...")
fullCovAssumption(dataset,dataset, cs,cs)
sharedCovAssumption(dataset,dataset, cs,cs)
for i in range(10):
    print("V = {0}".format(i+1))
    crossValidation(i, dataset,cs)

