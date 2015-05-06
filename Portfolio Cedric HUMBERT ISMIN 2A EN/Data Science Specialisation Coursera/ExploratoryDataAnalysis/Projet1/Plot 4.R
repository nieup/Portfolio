##      PLOT 4 : 
## 
## Extraction data from file : 
data <- read.table("household_power_consumption.txt", header = TRUE, sep = ";", na.string = "?", quote = "")
dataSel1 <- subset(data, data$Date == "1/2/2007")
dataSel2 <- subset(data, data$Date == "2/2/2007")
dataSel <- rbind(dataSel1, dataSel2) ## binding data from the 2 days

## Plot 4: 
par(mfrow = c(2, 2))
## Graph 1 : 
plot(dataSel$Global_active_power, xlab = "", ylab = "Global Active Power (kilowatts)", type = "l", xaxt = "n")
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))
## Graph 2 : 
plot(dataSel$Voltage,  xlab = "datetime", ylab = "Voltage", type = "l", xaxt = "n")
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))
## Graph 3 : 
plot(dataSel$Sub_metering_1 , ylab = "Energy sub metering", type = "l", xlab ="", xaxt = "n")
par(new = T) 
lines(dataSel$Sub_metering_2, col ="red")
lines(dataSel$Sub_metering_3, col ="blue")
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))
legend('topright', c("Sub_metrering_1", "Sub_metrering_2", "Sub_metrering_3"), lty = 1 , col = c("black", "red", "blue"), bty = "n")
## Graph 4 : 
plot(dataSel$ Global_reactive_power, xlab = "datetime", ylab = "Global Active Power (kilowatts)", type = "l", xaxt = "n")
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))
## Attriutes : 

## Saving file : 
png(file = "Plot 4.png")
dev.off()