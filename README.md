The Point class is designed to represent a three-dimensional point that is used to define the
vertices of polygons, whether they have any number of sides or are convex shapes. It also serves
as the center for circular shapes like circles and ellipses. The class includes various arithmetic
operators that have been overloaded to simplify vector and point calculations.
The Shape class acts as an abstract base class, providing a set of methods that must be
implemented by any class inheriting from it. In this scenario, we have the Polygon and
CircularShape classes derived from Shape.

Within the Polygon class, there are three private members: vertices, which stores the initial and
transformed states of the polygon, and the center of the polygon. However, no validation is
currently performed on the polygon vertices to ensure they form a valid convex shape.
For collision detection during object movement, dragging, or rotation, two methods are utilized.
The first approach calculates a bounding box (always a rectangle) for the polygon using the
"calculateBoundingBox()" function. This bounding box is then employed in the
"collidesWithOther()" method to determine if there are any collisions with other objects in the
Scene when the object is moved or rotated.

To address the issue of false positive detections, an alternative method known as the Separation
Axis Theorem is employed (only applicable for convex shapes). This technique is used in the
"intersection()" function to achieve more accurate collision detection results. The Separation
Axis Theorem helps identify overlaps or separations between shapes, enabling a more precise
assessment of collision occurrences.
In the "move" function, which handles object movement from the starting position (center of the
object) to the end position, collision detection is performed after each movement. The
"neighborsShapes" function is used to check for collisions specifically among neighboring
objects in the Scene, as it may contain several shape objects that we do not need to check for
collision.

The Scene class serves as a Singleton container for all shape objects. When shape objects are
created, they are mapped to the Scene's coordinate system. The player's playing pieces are
randomly selected from the pool of shape objects added to the scene.
In the Game class, shape objects are instantiated, and parameters such as end position,
movement step, and rotation step are set. The methods "movePlayingPieces" and
"rotatePlayingPieces" are used to handle the movement and rotation of the playing pieces.
To assist users during their initial move, the "checkPossibleCollisions" function is implemented.
This function determines if there are any obstacles or other shapes obstructing the path
between the player's playing pieces and their destination, taking into account the shortest
distance.

Since the code for circular shapes was not fully implemented, dynamic binding was not achieved
for functions such as "move" and "rotate". Consequently, only polygons were utilized in the
code.
