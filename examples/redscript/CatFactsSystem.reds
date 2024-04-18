// Copy file into r6\scripts\Awesome\
import Codeware.*
import RedData.Json.*
import RedHttpClient.*

public struct CatFactDto {
  public let createdAt: String;
  public let updatedAt: String;
  public let text: String;

  public static func CreateFromArray(json: ref<JsonArray>) -> array<CatFactDto> {
    let facts: array<CatFactDto> = [];
    let size: Uint32 = json.GetSize();
    let i: Uint32 = 0u;

    while i < size {
      let fact = CatFactDto.Create(json.GetItem(i) as JsonObject);

      ArrayPush(facts, fact);
      i += 1u;
    }
    return facts;
  }

  public static func Create(fact: ref<JsonObject>) -> CatFactDto {
    let self: CatFactDto;

    self.createdAt = fact.GetKeyString("createdAt");
    self.updatedAt = fact.GetKeyString("updatedAt");
    self.text = fact.GetKeyString("text");
    return self;
  }
}

public class CatFactsSystem extends ScriptableSystem {
  private let m_callbackSystem: wref<CallbackSystem>;

  /// Lifecycle ///

  private func OnAttach() {
    this.m_callbackSystem = GameInstance.GetCallbackSystem();
    this.m_callbackSystem.RegisterCallback(n"Session/Ready", this, n"OnSessionReady");
  }

  private func OnDetach() {
    this.m_callbackSystem.UnregisterCallback(n"Session/Ready", this, n"OnSessionReady");
    this.m_callbackSystem = null;
  }

  /// Game events ///

  private cb func OnSessionReady(event: ref<GameSessionEvent>) {
    let isPreGame = event.IsPreGame();

    if !isPreGame {
      return;
    }
    LogChannel(n"Info", s"== RedHttpClient - Examples ==");
    this.Example_CatFacts();
  }

  private func Shutdown() {
    LogChannel(n"Info", "");
    LogChannel(n"Info", s"== RedHttpClient - Examples ==");
  }

  /// Examples ///

  public func Example_CatFacts() {
    LogChannel(n"Info", "");
    LogChannel(n"Info", "== Cat Facts Api ==");
    let callback = HttpCallback.Create(this, n"OnCatFacts");

    AsyncHttpClient.Get(callback, "https://cat-fact.herokuapp.com/facts");
    LogChannel(n"Info", "Sending request...");
  }

  private cb func OnCatFacts(response: ref<HttpResponse>) {
    if !Equals(response.GetStatus(), HttpStatus.OK) {
      LogChannel(n"Info", s"Request failed, status code: \(response.GetStatusCode())");
      this.Shutdown();
      return;
    }
    let contentType = response.GetHeader("Content-Type");

    if !Equals(contentType, "application/json; charset=utf-8") {
      LogChannel(n"Info", s"Request failed, Json expected instead of '\(contentType)'.");
      this.Shutdown();
      return;
    }
    let json = response.GetJson();

    if !json.IsArray() {
      LogChannel(n"Info", s"Request failed, JsonArray expected instead of '\(json.GetClassName())'.");
      this.Shutdown();
      return;
    }
    let facts: array<CatFactDto> = CatFactDto.CreateFromArray(json as JsonArray);

    LogChannel(n"Info", s"\(ArraySize(facts)) cat facts:");
    for fact in facts {
      LogChannel(n"Info", s"---------------------------------------------");
      LogChannel(n"Info", s"Creation: \(fact.createdAt)");
      LogChannel(n"Info", s"Modification: \(fact.updatedAt)");
      LogChannel(n"Info", s"Fact: \(fact.text)");
    }
    this.Shutdown();
  }

}
