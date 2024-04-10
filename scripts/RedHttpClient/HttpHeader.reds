public native struct HttpHeader {

  public static func Create(name: String, value: String) -> HttpHeader {
    let self: HttpHeader;

    self.name = name;
    self.value = value;
    return self;
  }

  public native let name: String;
  public native let value: String;

}