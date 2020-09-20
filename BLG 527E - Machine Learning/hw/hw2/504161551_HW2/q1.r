# BLG 527E Machine Learning HW2 Q1
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

# Calculate within-class common variance matrix
S_W <- matrix(0, feature_num, feature_num)
for(cl in 1:class_num) {
  class_sc_mat = matrix(0, feature_num, feature_num)
  inClassSet = trainingSet[trainingSet$V65 == cl-1, ]
  for(row in 1:nrow(inClassSet)) {
    K <- t(inClassSet[row,1:feature_num] - t(m[cl,])) / nrow(trainingSet)
    class_sc_mat <- class_sc_mat + K %*% t(K)
  }
  S_W <- S_W + nrow(trainingSet[trainingSet$V65 == cl-1, ]) * class_sc_mat
}

# get diogonal of common variance matrix
s_diog <- diag(S_W)
s_diog_rms = sqrt(sum(s_diog^2)/length(s_diog))

# g(X) function when common covariance matrix is digonal
g_diogonal <- function(x, i) {
  summation <- 0
  for(j in 1:feature_num){
    summation <- summation + ((x[j] - m[i+1,j]) ^ 2) / s_diog[j]
  }
  (-1/2) * summation + log(nrow(trainingSet[trainingSet$V65 == i, ]) / nrow(trainingSet))
}


# g(X) function when common covariance matrix is s2i
g_s2i <- function(x, i) {
  summation <- 0
  for(j in 1:feature_num){
    summation <- summation + ((x[j] - m[i+1,j]) ^ 2) / s_diog_rms
  }
  (-1/2) * summation + log(nrow(trainingSet[trainingSet$V65 == i, ]) / nrow(trainingSet))
}


# Run classification function g_diogonal for training set
pred_tra_diogonal <- vector(length=nrow(trainingSet))
truth_tra_diogonal <- vector(length=nrow(trainingSet))
for (line in 1:nrow(trainingSet)) {
  # initialy select as class 0
  highest <- g_diogonal(trainingSet[line,], 0)
  selection <- 0
  for(i in 1:9) {
    output <- g_diogonal(trainingSet[line,], i)
    if (output > highest) {
      highest <- output
      selection <- i
    }
  }
  pred_tra_diogonal[line] <- selection
  truth_tra_diogonal[line] <- trainingSet[line, 'V65']
}

# Run classification function g_diogonal for test set
pred_test_diogonal <- vector(length=nrow(testSet))
truth_test_diogonal <- vector(length=nrow(testSet))
for (line in 1:nrow(testSet)) {
  # initialy select as class 0
  highest <- g_diogonal(testSet[line,], 0)
  selection <- 0
  for(i in 1:9) {
    output <- g_diogonal(testSet[line,], i)
    if (output > highest) {
      highest <- output
      selection <- i
    }
  }
  pred_test_diogonal[line] <- selection
  truth_test_diogonal[line] <- testSet[line, 'V65']
}



# Run classification function g_s2i for training set
pred_tra_s2i <- vector(length=nrow(trainingSet))
truth_tra_s2i <- vector(length=nrow(trainingSet))
for (line in 1:nrow(trainingSet)) {
  # initialy select as class 0
  highest <- g_s2i(trainingSet[line,], 0)
  selection <- 0
  for(i in 1:9) {
    output <- g_s2i(trainingSet[line,], i)
    if (output > highest) {
      highest <- output
      selection <- i
    }
  }
  pred_tra_s2i[line] <- selection
  truth_tra_s2i[line] <- trainingSet[line, 'V65']
}

# Run classification function g_s2i for test set
pred_test_s2i <- vector(length=nrow(testSet))
truth_test_s2i <- vector(length=nrow(testSet))
for (line in 1:nrow(testSet)) {
  # initialy select as class 0
  highest <- g_s2i(testSet[line,], 0)
  selection <- 0
  for(i in 1:9) {
    output <- g_s2i(testSet[line,], i)
    if (output > highest) {
      highest <- output
      selection <- i
    }
  }
  pred_test_s2i[line] <- selection
  truth_test_s2i[line] <- testSet[line, 'V65']
}


# Cretae confusion matrix
conf_tra_diogonal <- table(pred_tra_diogonal, truth_tra_diogonal)
conf_test_diogonal <- table(pred_test_diogonal, truth_test_diogonal)

conf_tra_s2i <- table(pred_tra_s2i, truth_tra_s2i)
conf_test_s2i <- table(pred_test_s2i, truth_test_s2i)

# Calculate error
tra_err_cnt_diogonal <- 0
for (line in 1:nrow(trainingSet)) {
  if (pred_tra_diogonal[line] != truth_tra_diogonal[line]) {
    tra_err_cnt_diogonal <- tra_err_cnt_diogonal +1
  }
}
tra_err_diogonal <- (tra_err_cnt_diogonal / nrow(trainingSet)) * 100

test_err_cnt_diogonal <- 0
for (line in 1:nrow(testSet)) {
  if (pred_test_diogonal[line] != truth_test_diogonal[line]) {
    test_err_cnt_diogonal <- test_err_cnt_diogonal +1
  }
}
test_err_diogonal <- (test_err_cnt_diogonal / nrow(testSet)) * 100

tra_err_cnt_s2i <- 0
for (line in 1:nrow(trainingSet)) {
  if (pred_tra_s2i[line] != truth_tra_s2i[line]) {
    tra_err_cnt_s2i <- tra_err_cnt_s2i +1
  }
}
tra_err_s2i <- (tra_err_cnt_s2i / nrow(trainingSet)) * 100

test_err_cnt_s2i <- 0
for (line in 1:nrow(testSet)) {
  if (pred_test_s2i[line] != truth_test_s2i[line]) {
    test_err_cnt_s2i <- test_err_cnt_s2i +1
  }
}
test_err_s2i <- (test_err_cnt_s2i / nrow(testSet)) * 100


test_err_diogonal_vector <- vector(length=class_num)
for (line in 1:nrow(conf_test_diogonal)) {
  test_err_diogonal_vector[line] <- ((sum(conf_test_diogonal[line,]) - conf_test_diogonal[line, line]) / sum(conf_test_diogonal[line,])) * 100
}

test_err_s2i_vector <- vector(length=class_num)
for (line in 1:nrow(conf_test_s2i)) {
  test_err_s2i_vector[line] <- ((sum(conf_test_s2i[line,]) - conf_test_s2i[line, line]) / sum(conf_test_s2i[line,])) * 100
}

# Write results to output file
outputFile <- "output.txt"

cat("Training error of Q1a:\n",file=outputFile)
cat(tra_err_diogonal,file=outputFile,append=TRUE)

cat("\n\nTest error of Q1a:\n",file=outputFile,append=TRUE)
cat(test_err_diogonal,file=outputFile,append=TRUE)

cat("\n\nTraining error of Q1b:\n",file=outputFile,append=TRUE)
cat(tra_err_s2i,file=outputFile,append=TRUE)

cat("\n\nTest error of Q1b:\n",file=outputFile,append=TRUE)
cat(test_err_s2i,file=outputFile,append=TRUE)

cat("\n\nTest error for each class for Q1a:\n",file=outputFile,append=TRUE)
cat(test_err_diogonal_vector,file=outputFile,append=TRUE)

cat("\n\nTest error for each class for Q1b:\n",file=outputFile,append=TRUE)
cat(test_err_s2i_vector,file=outputFile,append=TRUE)

cat("\n\n\n",file=outputFile,append=TRUE)

sink("output.txt", append = TRUE)

# Confusion matrix of the Q1a:
conf_test_diogonal

# Confusion matrix of the Q1b:
conf_test_s2i

sink()