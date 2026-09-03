cupSize 	= 50;
armLength	= 100;

module cup()
{
	difference()
	{
		union()
		{
			arm();
			sphere(d = cupSize);
		}
		union()
		{
			sphere(d = cupSize-2);
			translate([0,-cupSize/2,-cupSize/2])
			cube ([cupSize/2,cupSize,cupSize]);
		}
	}
}

module arm()
{
	difference()
	{
		translate ([-10,0,-2])
		union()
		{	
			rotate([-90,0,0])
			translate ([0,-2.5,0])
			cylinder (d= 4, h= armLength);
			cube ([10, armLength, 4]);
		}
		
		// Mounting Holes
		translate ([-5,armLength - 4,0])
		cylinder (d= 4, h= 6, center = true);	
		translate ([-5,armLength - 10,0])
		cylinder (d= 4, h= 6, center = true);
	}	
}

//	cup();


module hub()
{
	
	cylinder (d=cupSize, h=5, center = true);
	
	// Mounting Pins…
	translate ([0,0,2.5])
	for ( i = [0 : 2] )
	{
		rotate( i * 360 / 3, [0, 0, 1])
		translate ([0,8,0])
		{
			cylinder (d1= 4, d2 = 3, h = 6);
			translate ([0,6,0])
			cylinder (d1= 4, d2 = 3, h = 6);
		}
	}
}

module hubCap()
{
	difference()
	{
		sphere(d=cupSize);
		hub();
		translate([0,0, -cupSize / 2])
		xcube ([cupSize, cupSize, cupSize], center=true);
	}
}




hubCap();