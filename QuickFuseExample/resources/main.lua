-- Your app starts here!
print("This is my app!")
director:startRendering()

local qFuse
local zone = nil -- Ad a zone or leave nil for default zone.
local adAvailable = false

-- No reason for this I just wanted something to see other than blackness.
director:createCircle(director.displayCenterX, director.displayCenterY, 20)
-- End of circle.

if quick.QFuse:isAvailable() then
  qFuse = quick.QFuse:new()
  qFuse:init("<replace with app id>") -- This is your app id.
  
end

local onTimerClick = function(event)
  
  if qFuse == nil then
    return
  end
  
  if adAvailable then
    qFuse:show(zone) -- I show the ad every 30 seconds for this example.
  else
    qFuse:load(zone) -- If we don't have one. Ask for another.
  end
end

system:addTimer(onTimerClick, 30, -1)  -- 30 seconds timer to show ad.

function fuseHandler(event) -- Event call back. Not all are shown in this example.
  
  print("-----Event type:"..event.type)
  if event.type == "AdAvailableResponse" then -- Called after you request a load.
     print("-----Available:")
     print(event.available) -- If it is > 0 then you have an ad.
     print("----Error:")
     print(event.error) -- If it is > 0  then you had an error.
     
     if event.available == 0 then
       adAvailable = false; -- We didn't get one. If both available and error are 0 it means no fill.
     else
       adAvailable = true;
     end
  end
  
  if event.type == "SessionReceived" then -- Called when session is successfully started.
    qFuse:load(zone) -- Ask for an ad after we know that the session was started.
  end
  
  if event.type == "AdWasClosed" then -- Called when ad is closed. 
    qFuse:load(zone)
  end
  
  if event.type == "RewardedAdCompleted" then -- Called when reward video was mostly shown.
    print("Reward Item:"..event.rewardItem)
    print("Reward Amount:"..event.rewardAmount)
    qFuse:load(zone)
  end
end

system:addEventListener("fuseAds", fuseHandler) -- Register the call back.