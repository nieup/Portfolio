##      PLOT 3 : 
## 
## Extraction data from file : 
data <- read.table("household_power_consumption.txt", header = TRUE, sep = ";", na.string = "?", quote = "")
dataSel1 <- subset(data, data$Date == "1/2/2007")
dataSel2 <- subset(data, data$Date == "2/2/2007")
dataSel <- rbind(dataSel1, dataSel2) ## binding data from the 2 days

## Plot 3: 
plot(dataSel$Sub_metering_1 , ylab = "Energy sub metering", type = "l", xlab ="", xaxt = "n")

## Attriutes : 
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))
par(new = T) 
lines(dataSel$Sub_metering_2, col ="red")
lines(dataSel$Sub_metering_3, col ="blue")
## Legend : 
legend('topright', c("Sub_metrering_1", "Sub_metrering_2", "Sub_metrering_3"), lty = 2 , col = c("black", "red", "blue"))

## Saving file : 
png(file = "Plot 3.png")
dev.off()