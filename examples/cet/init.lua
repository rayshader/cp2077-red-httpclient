-- Copy file into bin\x64\plugins\cyber_engine_tweaks\mods\AwesomeExample\
listener = {}

registerForEvent('onInit', function()
  print("== RedHttpClient - Examples ==")
  Example_CatFacts()
end)

function Shutdown()
  print("== RedHttpClient - Examples ==")
end

function Example_CatFacts()
  print("")
  print("== Cat Facts Api ==")
  listener = NewProxy({
    OnCatFacts = {
      args = { "handle:HttpResponse" },
      callback = function(response) Example_OnCatFacts(response) end
    }
  })
  local callback = HttpCallback.Create(listener:Target(), listener:Function("OnCatFacts"))

  AsyncHttpClient.Get(callback, "https://cat-fact.herokuapp.com/facts")
  print("Sending request...")
end

function Example_OnCatFacts(response)
  if response:GetStatusCode() ~= 200 then
    print("Request failed, status code: " .. tostring(response:GetStatusCode()))
    Shutdown()
  end
  local contentType = response:GetHeader("Content-Type")

  if contentType ~= "application/json; charset=utf-8" then
    print("Request failed, Json expected instead of '" .. contentType .. "'.")
    Shutdown()
  end
  local data = response:GetText()
  local facts = json.decode(data)

  print(tostring(#facts) .. " cat facts:")
  for _, fact in ipairs(facts) do
    print("---------------------------------------------")
    print("Creation: " .. fact.createdAt)
    print("Modification: " .. fact.updatedAt)
    print("Fact: " .. fact.text)
  end
  Shutdown()
end
