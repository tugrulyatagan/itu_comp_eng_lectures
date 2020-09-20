# BLG 527E Machine Learning HW2 Q2
# Author: Tugrul Yatagan 504161551

# Read data from file
trainingFile <- "optdigits.tra"
testFile <- "optdigits.tes.txt"

trainingSet <- read.table(trainingFile, sep=",")
testSet <- read.table(testFile, sep=",")

# Find and eleminate all 0 coloumns in trainig data
trainingSet <- trainingSet[,colSums(trainingSet^2) !=0]
feature_num <- ncol(trainingSet) - 1
class_num <- 10
testSet<-testSet[,-c(1,40)]


# Calculate mean mij matrix
m <- matrix(0, class_num, feature_num)
for(cl in 1:class_num) {
  inClassSet = trainingSet[trainingSet$V65 == cl-1, ]
  m[cl,] <- sapply(inClassSet[1:feature_num], mean)
}

# Calculate within-class scatter matrix
S_W <- matrix(0, feature_num, feature_num)
for(cl in 1:class_num) {
  class_sc_mat = matrix(0, feature_num, feature_num)
  inClassSet = trainingSet[trainingSet$V65 == cl-1, ]
  for(row in 1:nrow(inClassSet)) {
    K <- t(inClassSet[row,1:feature_num] - t(m[cl,]))
    class_sc_mat <- class_sc_mat + K %*% t(K)
  }
  S_W <- S_W + class_sc_mat
}

# Calculate between-class scatter matrix
overall_m = sapply(trainingSet[1:feature_num], mean)
S_B <- matrix(0, feature_num, feature_num)
for(cl in 1:class_num) {
  S_B <- S_B + nrow(trainingSet[trainingSet$V65 == cl-1, ]) * (m[cl,] - overall_m) %*% t(m[cl,] - overall_m)
}

# Solving the generalized eigenvalue problem for the matrix
eig <- eigen(solve(S_W) %*% S_B)

# Transforming the samples onto the new subspace
tra_lda <- as.matrix(trainingSet[,1:feature_num]) %*% Re(eig$vec[,1:2])
test_lda <- as.matrix(testSet[,1:feature_num]) %*% Re(eig$vec[,1:2])

# Visualize
# Training set
dev.new()
plot(tra_lda)
text(x = tra_lda[,1], y = tra_lda[,2], labels=trainingSet$V65, cex= 0.7, pos=3)
title(main="Training data")

# Test set
dev.new()
plot(test_lda)
text(x = test_lda[,1], y = test_lda[,2], labels=testSet$V65, cex= 0.7, pos=3)
title(main="Test data")
