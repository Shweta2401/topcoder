png(file="source.png")
par(bg="grey95", mar=c(4,4,1,1), mfrow=c(2,1))
wave <- read.table("f1.dat")
plot(wave$V1, type="l")
wave <- read.table("f2.dat")
plot(wave$V1, type="l")
dev.off()
