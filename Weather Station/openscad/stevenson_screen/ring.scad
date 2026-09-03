/*

	Stevenson Screen Assembly for Skippy's Weather Station, written in OpenScad by Skippy - https://skippy.org.uk
	
	© 2014 Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) - http://creativecommons.org/licenses/by-nc-sa/4.0/

	Visualy Based on work by Kowomike - http://www.thingiverse.com/thing:158039

*/
// Variables

	diameter	=	80;	// External Diameter 
	louveSize	=	10;
	tubeID		=	15;
	$fn			=	100; 	// 100 for quick, anything more and grab a nice cup of tea…

// Things to Use
	use <../../../Vitamins/OpenScad/MCAD/nuts_and_bolts.scad>
	use <../../../Vitamins/OpenScad/MCAD/regular_shapes.scad>
				// Provides us with cylinder_tube & triangle

module louve()
{
	rotate_extrude() 
	translate ([diameter/ 2 - (louveSize * 0.9) , 8, 0]) // I am not sure why the 0.9 is required.
	scale ([1,1.5,1])
	difference ()
	{
		triangle(louveSize);
		translate ([0,-2,0])
		triangle(louveSize);
	}

}

module ring()
{
	difference ()
	{
		union()
		{
			louve();
			// Tubes for rods for mounting rings together
			for ( i = [0 : 3] )
			{
				rotate(i * 360 / 4, [0, 0, 1])
				translate([0, diameter/2.55, 10])
				cylinder_tube(20, 5, 2, true);
			}
		}
		for ( i = [0 : 3] )
		{
			rotate( i * 360 / 4, [0, 0, 1])
			{
				translate([0, diameter/2.55, -1])
				{
					cylinder(22, d = 7, true);
					cylinder(24, d = 7, true);
					
					// Nut Traps
					translate([0, 0, .5])
					nutHole(6);
				}
				translate([0, diameter/2.45, 20])
				cylinder(10, d = 12, true);
			}
		}
	}
}

module base()
{
	intersection ()	//Hacky way to make the bottom flat
	{
		union()
		{
			// need to remove height from this to clean up bottom
			translate ([0,0,-1])
			ring();
	
			// Arms linking the mounting cylinder to the Ring
			for ( i = [0 : 179] )
			{
				rotate( i * 360 / 20, 1)
				translate([-1, diameter/9, 0])
				{
					cube([2, diameter / 4.3,10]);
					rotate([90, 0, 0])
					translate([1, 10, 17.5])
					cylinder(h = diameter / 4.2, d = 2);
				}
			}
			// Central Mounting Cylinder
			translate ([0,0,10])
			cylinder_tube(20, (tubeID + 8)/2, 3, true);
			translate ([0,0,20])
			cylinder_tube(5, (tubeID + 8 )/2, 8, true);
		}
		translate ([0,0,12.5])
		cube ([diameter + 10,diameter + 10,25],center=true);
	}


}
 
base();