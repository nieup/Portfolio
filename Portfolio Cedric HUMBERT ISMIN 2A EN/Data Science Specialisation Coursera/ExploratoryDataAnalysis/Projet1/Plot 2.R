##      PLOT 2 : 
## 
## Extraction data from file : 
data <- read.table("household_power_consumption.txt", header = TRUE, sep = ";", na.string = "?", quote = "")
dataSel1 <- subset(data, data$Date == "1/2/2007")
dataSel2 <- subset(data, data$Date == "2/2/2007")
dataSel <- rbind(dataSel1, dataSel2) ## binding data from the 2 days

## Plot 2: 
plot(dataSel$Global_active_power, xlab = "", ylab = "Global Active Power (kilowatts)", type = "l", xaxt = "n")
## Attriutes : 
axis(1, at = 1:3, labels = c("Thu", "Fri", "Sat"))

## Saving file : 
png(file = "Plot 2.png")
dev.off()