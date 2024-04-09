public native struct HttpPair {

  public static func Create(key: String, value: String) -> HttpPair {
    let self: HttpPair;

    self.key = key;
    self.value = value;
    return self;
  }

  public native let key: String;
  public native let value: String;

}