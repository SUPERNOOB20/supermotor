namespace supermotor
{
    namespace essentials
    {

        int gallery_update(int your_gallery, int number_of_images){

            your_gallery = your_gallery % number_of_images;            // Loops the gallery around to keep the indices small.

            if (your_gallery < 0){
                your_gallery = number_of_images + your_gallery;       //  Usually this silly extra step wouldn't be needed, but modulo in cpp is... weird? For negative numbers ":3
            }

            return your_gallery;
        }

    }
}
