function SaveToLuaFile(fileName, outputString, overwrite)
   print("SaveToLuaFile...")
   local f;						-- The file
   if overwrite == 1 then		-- Wipe the contents with new data
      f = assert(io.open(fileName, "w"))
   elseif overwrite == 0 then	-- Append with new data
      f = assert(io.open(fileName, "a"))
   end
   -- Write to the file
   f:write(outputString)
   -- Close the file
   f:close()
   print("OK")
end

function Random(from, to, result)
	math.randomseed(os.time())
	result = math.random(from, to)
	return result;
end