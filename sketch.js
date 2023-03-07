function setup() {
	createCanvas(windowWidth, windowHeight);
}

function draw() {
	// Draw a white background
	background(255);
		
	// Retrieve the data being sent from render.cpp
	// Format: 
	let data = Bela.data.buffers[0];
    console.log(data)

	// Draw a circle whose position reflects XY acceleration
	// let xPos = windowWidth / 2 + imudata[0] * windowWidth / 2;
	// let yPos = windowHeight / 2 + imudata[1] * windowHeight / 2;
	
	// noStroke();
	// fill(0, 0, 255);
	// ellipse(xPos, yPos, windowWidth * 0.1, windowWidth * 0.1);
	
	// // Draw another circle whose position reflects XY gyro data
	// // Axes reordered and inverted to match the directionality of the accelerometer
	// xPos = windowWidth / 2 - imudata[4] * windowWidth * .01;
	// yPos = windowHeight / 2 + imudata[3] * windowHeight * .01;
	
	// noStroke();
	// fill(0, 128, 0);
	// ellipse(xPos, yPos, windowWidth * 0.1, windowWidth * 0.1);	
}
