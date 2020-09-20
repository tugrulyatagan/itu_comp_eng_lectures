################################
#    Workshop
################################

x <- 1
class(x)

x <- 1:5
class(x)

x[1]

x <- 1:5
y <- c("a","b","c","d","e")

myDf <- data.frame(myInteger=x,myString=y,stringsAsFactors = F)
class(myDf)
myDf[,2]
class(myDf[,2])
as.character(myDf[,2])
myDf[,2]
myDf$myString

matrix(1:9,nrow = 3)
matrix(1:9,nrow = 3,byrow = T)
##############################################

x <- rnorm(500,mean = 0,sd = 1)
plot(x)
y <- rnorm(500, 5, 2)

tmp <- data.frame(y,x)

head(tmp,n = 10)
tail(tmp,n = 10)

summary(tmp[,1])

sapply(tmp, function(x) max(x))

maxof <- numeric()
for(i in 1:2){
  maxof[i] <- max(tmp[,i])
}
maxof

sapply(tmp, function(x) max(x))
rowMax <- apply(tmp, MARGIN = 2, function(x) max(x))
head(rowMax)

myList <- list(myInteger=1, myVector=1:10, myDf = tmp)
class(myList)
class(myList[1:2])
class(myList[[3]])

head(myList$myDf$y)
head(myList[[3]][[1]])


myList2 <- list(myMat = matrix(1:9,3)) -> myList3
myList2
for(i in 1:10){
  myList2[[1]] <- rbind(myList2[[1]], c(1:3))
}

myList2

length(myList)
lapply(myList, class)
lapply(myList, dim)
lapply(myList, function(x){
  ### do sth
  #
  #
  #return(sth)
})

#install.packages("dtree")
library(dtree)





####################
#   HW 1 like
####################

meanVec <- numeric()
for(i in 1:500){
  meanVec[i] <- mean(rnorm(n = 10,mean = 0, sd = 1)) 
}

hist(meanVec,breaks = 50, main = "myPlot",xlab = "myX",ylab = "myY",ylim = c(0,50))

meanVec1 <- sapply(1:500, function(x){
  myRand <- rnorm(10,0,1)
  myMean <- mean(myRand)
  # return(myMean)
  myMean
})

hist(meanVec1,breaks = 50, main = "myPlot",xlab = "myX",ylab = "myY",ylim = c(0,50))

##############################################

meanVec1 <- sapply(1:500, function(x){
  myRand <- rnorm(100,0,1)
  myMean <- mean(myRand)
  # return(myMean)
  myMean
})

hist(meanVec1,breaks = 50, main = "myPlot",xlab = "myX",ylab = "myY")


####################

install.packages("ggplot2")

sampleSize <- 100000
pC1 <- 0.2

c1 <- rnorm(sampleSize*pC1,0,1)
c2 <- rnorm(sampleSize*(1-pC1),1,5)

hist(c(c1,c2),breaks = 1000,probability = T,ylim = c(0,0.5))
lines(density(c1),col=2)
lines(density(c2),col=3)

c1DF <- data.frame(class = "c1", l=c1)
c2DF <- data.frame(class = "c2", l=c2)
head(c1DF)

tmp1 <- density(c1,from = min(c(c1,c2)),to = max(c(c1,c2)))
tmp2 <- density(c2,from = min(c(c1,c2)),to = max(c(c1,c2)))

# png("asdasdasd")
plot(tmp1,type="l")
lines(tmp2,col=2)
# dev.off()

tmp <- cbind(tmp1$y, tmp2$y)
a1 <- tmp[,1]/rowSums(tmp)
a2 <- tmp[,2]/rowSums(tmp)

# pdf("~/../Desktop/myPlot.pdf")
plot(tmp1$x,a1,type = "l",ylim=c(0,1))
lines(tmp1$x,a2,col=2)
# dev.off()

plot(tmp1$x, sapply(tmp1$x, function(x) -0.5*log(2*pi) - log(1) - x^2/2 + log(0.2)),type = "l",col=2, xlim = c())
lines(tmp1$x, sapply(tmp1$x, function(x) -0.5*log(2*pi) - log(1) - (x-1)^2/4 + log(0.8)),col=3)

