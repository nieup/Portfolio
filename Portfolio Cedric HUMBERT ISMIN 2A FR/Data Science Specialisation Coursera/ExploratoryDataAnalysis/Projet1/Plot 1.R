##      PLOT 1 : 
## 
## Extraction data from file : 
data <- read.table("household_power_consumption.txt", header = TRUE, sep = ";", na.string = "?", quote = "")
dataSel1 <- subset(data, data$Date == "1/2/2007")
dataSel2 <- subset(data, data$Date == "2/2/2007")
dataSel <- rbind(dataSel1, dataSel2) ## binding data from the 2 days

## Plot : 
hist(dataSel$Global_active_power, xlab = "Global Active Power (kilowatts)", ylab = "Frequency", col="red", main = NULL)
## Attriutes : 
title("Global Active Power")

## Saving file : 
png(file = "Plot 1.png")
dev.off()