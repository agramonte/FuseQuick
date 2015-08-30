# FuseQuick
Quick binding for Fuse

Quick Binding for FusePowered Ads.

1. Although I plan to create better documentation. Currently the only documentation is found in the QuickFuseExample Quick lua code. I tried to document every line.

2. At this point I have only tested Reward Ads and Interstitial. Although I suspect the other types of ads work since they are very similar to Reward Ads.

How to integrate the Quick binding. The best instructions are on the marmalade site here:

http://docs.madewithmarmalade.com/display/MD/Extending+Quick

Here are the steps I took (not necessary the best way):

	1. I Downloaded the Fuse Marmalade extension from here:
		http://www.fusepowered.com/resources/

	2. I dropped the extension in the Marmalade extension folder but there are apparently better places and ways to do this. I opened up the FuseSDK.mkf and deleted the google support libraries from the deployment section. The Facebook extension included with Quick already has it and since both are using the old style of referencing they conflict.

	3. I copy the QFuse.cpp into the source folder in the quick folder and copy QFuse.h into the include folder in the quick folder. Again there are better way to this, I just don’t mind re-doing it every time a version of Marmalade comes out. 

	4. I modified my quickuser.mkf file and under files I add “souce/QFuse.cpp” and “include/QFuse.h”. I also add subproject{“FuseSDK”} to this file. 

	5. I run the quickuser_tolua file (quick folder).

	6. I run build_quick_prebuilt file (quick folder).

	7. I then created the Sample App Quick project using the hub. Android only: For some reason I have to always add the res folder path, the extra manifest permissions path and the extra manifest strings path to the project. All three were in the source android folder of the FuseSDK.

	8. I then opened the project using my C++ editor made sure the extension had loaded and rebuilt the entire project.

	9. Now I went back to the lua editor and added the code for the sample app.

I’ll try to do a video soon to make it easier to follow.
