// Basic animations for backgrounds and the like.








// Only horizontal and vertical animations at the moment.
// Will include diagonal animations in the future (diagonal atlas).
// Might include angles in the future (for animations that don't loop),
// but I have other features as a priority right now,
// cut me some slack...
//
// Direction can be:
// FOR VERTICAL ANIMATIONS:
// down
// up
// FOR HORIZONTAL ANIMATIONS:
// left
// right
// FOR DIAGONAL ANIMATIONS:
// downleft
// downright
// upleft
// upright
//
// I wonder if int could be replaced by something like Uint32 or uint32_t here...
// (e.g: It wouldn't make sense to have an image with negative resolution...)
static animate(const char* direction, Uint64 duration, int texture_height, int texture_width, Uint64 deltaTime){

    if texture_width == nullptr{
        animate_vertically();
    } else if texture_height == nullptr {
        animate_horizontally();
    } else {
        animate_diagonally();
    }
}
