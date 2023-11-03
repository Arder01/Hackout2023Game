# 5 Steps Away

# for textures
To create texture first load the teture on any surface wit
-->SDL_Surface *x = IMG_Load(file path); <--
Now convert img into texture with
-->SDL_Texture* t = SDL_CreateTexrtureFromSurface(renderer,x)<--//rendrer->SDL_Render component, x -> surface component
Now Render the texture using either method
-->SDL_RenderCopy or SDL_RenderCopyEx<--
-->SDL_RenderCopy(rendrer,t, &srcrect,&dstrect)<--//srcrect is SDL_Rect component that defines how much of the textue should be rendered, eg if the png is 256x96 and you want to render complet the set SDL_Rect srcrect = {0,0,256,96} i.e. draw from (0,0) to (256,96),
//dstrect is the destination of rendering and the size to be rendered {200,200,32,16} will render the image at (200,200) and will be scaled down to 32x16 i.e it will look small.

# for motion 
1. ake sure the pointers are initiated in constructor or .h file
2. to limit movement , simple if else 
3. Make sure that m_Position is >1 for +ve as when converted to int it rounds off. It created the problem where code was correct but PDrect was int and m_Position was float and less than 1, PDrect was being added 0.

# for xml reader
https://github.com/vmayoral/tinyxml
also add the tinyxml file directly to your folder too, else it will give LINK2019 and Link2001errors
just drag and drop the xml files from tinyxml  folder

